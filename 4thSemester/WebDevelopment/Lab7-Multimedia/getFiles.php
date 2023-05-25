<?php

$host = "localhost";
$username = "root";
$password = "";
$database = "multimedia_files";

$conn = mysqli_connect($host, $username, $password, $database);
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

$id = $_GET['id'];

try {
    $sql = "SELECT * FROM multimedia_file WHERE id = $id";
    $result = mysqli_query($conn, $sql);

    if (mysqli_num_rows($result) > 0) {
        $row = mysqli_fetch_assoc($result);
        $multimediaFile = array(
            'title' => $row['title'],
            'format' => $row['format'],
            'genre' => $row['genre'],
            'path' => $row['path']
        );
        echo json_encode([$multimediaFile]);
    } else {
        echo "Multimedia file not found.";
    }
} catch (Exception $e) {
    echo 'Exception: ', $e->getMessage(), "\n";
}

mysqli_close($conn);
