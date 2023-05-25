<?php
$con = new mysqli("localhost", "root", "", "multimedia_files");
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

if ($_SERVER["REQUEST_METHOD"] == "POST"){
    $id = mysqli_real_escape_string($con, $_POST["id"]);

    if ($id){
        $sql = "DELETE FROM multimedia_file WHERE id = '$id'";
        if ($con->query($sql)) {
            $response = array('success' => true, 'message' => 'Record deleted successfully.');
        } else {
            $response = array('success' => false, 'message' => 'Error deleting record: ' . mysqli_error($con));
        }
    } else {
        $response = array('success' => false, 'message' => 'Invalid ID parameter.');
    }

    mysqli_close($con);

    header('Content-Type: application/json');
    echo json_encode($response);
}
