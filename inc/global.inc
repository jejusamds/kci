<?php
error_reporting(E_ALL);
ini_set("display_errors", 0);

header("Content-Type: text/html; charset=UTF-8");

// 6시간으로 
ini_set('session.gc_maxlifetime', 21600);
session_set_cookie_params(21600);
@session_start();

@extract($_GET);
@extract($_POST);
@extract($_SERVER);
@extract($_FILES);

//require($_SERVER['DOCUMENT_ROOT'] . "/lib/Db.class.php");
require(__DIR__ . "/../lib/Db.class.php");
$db = new Db();

// 관리자 출력시 보안검증
function safeAdminOutput($input, $allowHtml = false)
{
    if ($allowHtml) {
        // HTML 태그는 허용하지만 위험한 요소 제거
        $input = preg_replace('/<(script|style|iframe|object|embed|applet|meta|link|title|base)[^>]*>.*?<\/\1>/is', '', $input);
        $input = preg_replace('/on\w+=".*?"/i', '', $input);
        $input = preg_replace('/javascript:[^"]*/i', '', $input);
        return strip_tags($input, '<b><i><u><p><a>');
    } else {
        // HTML 태그를 모두 비활성화
        return htmlspecialchars($input, ENT_QUOTES, 'UTF-8');
    }
}

// 에러 메세지 출력
function error($error_msg, $go_url = "")
{

    if ($go_url == "")
        echo "<script>alert(\"$error_msg\");history.go(-1);</script>";
    else
        echo "<script>alert(\"$error_msg\");document.location=\"$go_url\";</script>";
    exit;
}

function errorclose($error_msg)
{

    echo "<script>alert(\"$error_msg\");self.close();</script>";

    exit;
}

function errorcolorbox($error_msg)
{

    echo "<script>alert(\"$error_msg\");parent.$.colorbox.close();</script>";

    exit;
}
// 확인 메세지 출력
function confirms($confirm_msg, $go_url = "")
{

    if ($go_url == "") {
        echo "<script>if(confirm(\"$confirm_msg\"));history.go(-1);</script>";
    } else {
        echo "
			<script>
			if(confirm(\"$confirm_msg\")){
			document.location=\"$go_url\";
			}
			else {
			history.go(-1);
			}
			</script>";
    }
    exit;
}

// 완료 경고창 출력
function comalert($com_msg, $go_url = "")
{

    if ($go_url == "")
        echo "<script>alert(\"$com_msg\");history.go(-1);</script>";
    else
        echo "<script>alert(\"$com_msg\");document.location=\"$go_url\";</script>";
}

// 완료 메세지 출력
function complete($com_msg, $go_url = "")
{

    if ($go_url == "")
        echo "<script>window.setTimeout(\"history.go(-1)\",600);</script>";
    else
        echo "<script>window.setTimeout(\"document.location='$go_url';\",600);</script>";

    echo "<body><table width=100% height=100%><tr><td align=center><font size=2>$com_msg</font></td></tr></table></body>";
}


// partnership_sub01.html
$g_usage[1] = '업무/근생';
$g_usage[2] = '물류시설';
$g_usage[3] = '주거시설';
$g_usage[4] = '리모델링';
$g_usage[5] = '기타';


$g_area = [
'서울',
'부산',
'대구',
'인천',
'광주',
'대전',
'울산',
'세종',
'경기',
'강원',
'충북',
'충남',
'전북',
'전남',
'경북',
'경남',
'제주'
];

$gInquiry_gubun_name = array(
    'contact_us' => '메인 문의',
    'show' => '전시장 예약',
    'buy' => '제품구매',
    'dev' => '개발의뢰',
    'coalition' => '제휴문의',
    'as' => 'A/S 신청',
    'quick' => '빠른 상담'
);

$gDelivery_gubun[1] = '쉼터농막';
$gDelivery_gubun[2] = '주거숙박';
$gDelivery_gubun[3] = '상업공동시설';

if (!(isset($_SERVER['HTTPS']) && ($_SERVER['HTTPS'] == 'on' || $_SERVER['HTTPS'] == 1) || isset($_SERVER['HTTP_X_FORWARDED_PROTO']) && $_SERVER['HTTP_X_FORWARDED_PROTO'] == 'https')) {
    $redirect = 'https://' . $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI'];
    header('HTTP/1.1 301 Moved Permanently');
    header('Location: ' . $redirect);
    exit();
}
