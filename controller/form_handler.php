<?php
include $_SERVER['DOCUMENT_ROOT'] . '/inc/global.inc';
include $_SERVER['DOCUMENT_ROOT'] . '/inc/util_lib.inc';

header('Content-Type: application/json; charset=utf-8');

// 필수 값 검증
if (!isset($_POST['f_subject'], $_POST['f_name_company'], $_POST['f_phone'], $_POST['f_email'], $_POST['f_message'])) {
    echo json_encode(['result' => 'error', 'msg' => '필수 항목이 누락되었습니다.', 'post' => $_POST]);
    exit;
}

// DB 저장 (AS 문의 테이블 예시: df_site_form_as)
$subject = addslashes(trim($_POST['f_subject']));
$nameCompany = addslashes(trim($_POST['f_name_company']));
$phone = addslashes(trim($_POST['f_phone']));
$email = addslashes(trim($_POST['f_email']));
$contractProject = addslashes(trim($_POST['f_contract_project']));
$message = addslashes(trim($_POST['f_message']));

$attachmentName = '';
if (isset($_FILES['f_attachment']) && $_FILES['f_attachment']['error'] === UPLOAD_ERR_OK) {
    // 파일명만 저장 (원본 이름 그대로, 또는 별도 처리)
    $origName = $_FILES['f_attachment']['name'];
    $ext = strtolower(pathinfo($origName, PATHINFO_EXTENSION));
    $uniqName = 'as_' . time() . '.' . $ext;
    $uploadDir = $_SERVER['DOCUMENT_ROOT'] . '/userfiles/form_attachments/';
    if (!is_dir($uploadDir)) {
        mkdir($uploadDir, 0707, true);
    }
    $fullPath = $uploadDir . $uniqName;
    move_uploaded_file($_FILES['f_attachment']['tmp_name'], $fullPath);
    $attachmentName = $uniqName;
}

// SQL 삽입
$sql = "INSERT INTO df_site_form_as ";
$sql .= "(f_subject, f_name_company, f_phone, f_email, f_contract_project, f_attachment, f_message) ";
$sql .= "VALUES ";
$sql .= "('{$subject}','{$nameCompany}','{$phone}','{$email}','{$contractProject}','{$attachmentName}','{$message}')";
$db->query($sql);


$sql = "select g_manager_email from df_site_siteinfo";
$g_info = $db->row($sql);

// 사용자에게 “접수 완료” JSON 응답
echo json_encode(['result' => 'ok', 'msg' => '문의가 정상 접수되었습니다.', 'redirect' => '/']);
flush(); // 출력 버퍼 클리어

// 백그라운드로 메일 전송 실행
//    - CLI 경로: PHP_BINARY 또는 직접 php 경로
$possiblePhp = [
    '/usr/bin/php',               // 일반적인 리눅스 PHP CLI
    '/usr/local/bin/php',         // 어떤 공유 호스팅에선 여기에 설치됨
    '/usr/bin/php-cli',           // 또 다른 예시
    '/usr/local/php/bin/php',     // (호스팅마다 다르게 설치될 수 있음)
    PHP_BINDIR . '/php',          // PHP_BINDIR이 가리키는 디렉터리 + php
];

// 사용 가능한 PHP CLI 경로
$phpCli = null;
foreach ($possiblePhp as $path) {
    if (file_exists($path) && is_executable($path)) {
        $phpCli = $path;
        break;
    }
}

if ($phpCli === null) {
    $phpCli = '/usr/bin/php';
}

$worker = $_SERVER['DOCUMENT_ROOT'] . '/controller/mail_process.php';

$toEmail = $g_info['g_manager_email'];
$toName = '담당자';
$mailSub = "[AS 문의] " . $subject;
$mailBody = "
    <h2>AS 문의 접수</h2>
    <p><strong>제목:</strong> " . htmlspecialchars($subject, ENT_QUOTES) . "</p>
    <p><strong>이름/회사명:</strong> " . htmlspecialchars($nameCompany, ENT_QUOTES) . "</p>
    <p><strong>연락처:</strong> " . htmlspecialchars($phone, ENT_QUOTES) . "</p>
    <p><strong>이메일:</strong> " . htmlspecialchars($email, ENT_QUOTES) . "</p>
    <p><strong>계약공사명:</strong> " . htmlspecialchars($contractProject, ENT_QUOTES) . "</p>
    <p><strong>문의사항:</strong><br>" . nl2br(htmlspecialchars($_POST['f_message'], ENT_QUOTES)) . "</p>
";

// 첨부파일 절대 경로(없으면 빈 문자열)
$attachmentPath = '';
if ($attachmentName !== '') {
    $attachmentPath = $_SERVER['DOCUMENT_ROOT'] . '/userfiles/form_attachments/' . $attachmentName;
}

$cmdParts = [
    escapeshellcmd($phpCli),
    escapeshellarg($worker),
    escapeshellarg($toEmail),
    escapeshellarg($toName),
    escapeshellarg($mailSub),
    escapeshellarg($mailBody),
    escapeshellarg($email),
];
if ($attachmentPath !== '') {
    $cmdParts[] = escapeshellarg($attachmentPath);
}
$cmd = implode(' ', $cmdParts) . ' > /dev/null 2>&1 &';

// // debug 로그 남기기
// file_put_contents(__DIR__ . '/form_exec_log.txt',
//     date('[Y-m-d H:i:s] ') . "exec 명령: {$cmd}\n",
//     FILE_APPEND
// );

exec($cmd);