<?php
$host = '127.0.0.1';
$user = 'kci9874';
$pass = 'kci63707290!!@';
$db   = 'kci9874';

mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

try {
    $conn = new mysqli($host, $user, $pass, $db);
    echo "✅ MariaDB 접속 성공";
    $conn->close();
} catch (mysqli_sql_exception $e) {
    echo "❌ 오류 발생: " . $e->getMessage();
}
?>

