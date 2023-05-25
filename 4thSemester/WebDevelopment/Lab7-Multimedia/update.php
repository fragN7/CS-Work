<?php
session_start();

$con = new mysqli("localhost", "root", "", "multimedia_files");
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");

try {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $id = mysqli_real_escape_string($con, $_POST["Id"]);
        $title = mysqli_real_escape_string($con, $_POST["Title"]);
        $format = mysqli_real_escape_string($con, $_POST["Format"]);
        $genre = mysqli_real_escape_string($con, $_POST["Genre"]);
        $path = mysqli_real_escape_string($con, $_POST["Path"]);

        if (empty($title)) {
            $errors[] = 'Title is required.';
        }

        if (empty($format)) {
            $errors[] = 'Format is required.';
        }

        if (empty($genre)) {
            $errors[] = 'Genre is required.';
        }

        if (empty($path)) {
            $errors[] = 'Path is required.';
        } else {

            $dotPosition = strpos($path, '.');
            if ($dotPosition !== false) {
                $substringBeforeDot = substr($path, 0, $dotPosition);
                $filename = basename($substringBeforeDot); // Extract the filename from the substring before the dot
                $substringBeforeDot = pathinfo($filename, PATHINFO_FILENAME); // Extract the filename without the extension
                $substringAfterDot = substr($path, $dotPosition + 1);

                if($substringAfterDot != $format)
                    $errors[] = 'The format does not match the file extension in the path.';

                /*if($substringBeforeDot != $title)
                    $errors[] = 'The title does not match the file name in the path.';*/

            } else {
                $errors[] = 'Invalid path.';
            }
        }

        $checkQuery = "SELECT * FROM multimedia_file WHERE id = '$id'";
        $result = $con->query($checkQuery);

        if ($result->num_rows > 0 && empty($errors)) {
            // Title exists, perform the update
            $sql = "UPDATE multimedia_file SET title='$title', format='$format', genre='$genre', path='$path' WHERE (id = '$id')";
            $con->query($sql);
            echo 'Row Updated successfully.';
            //header("Location: browse.html");
        } else {
            foreach ($errors as $error) {
                echo $error . "<br>";
            }
            echo 'File does not exist in the database.';

            //header("Location: browse.html");
            exit();
        }

        mysqli_close($con);
    }
} catch (Exception $e) {
    echo 'Caught exception: ', $e->getMessage(), "\n";
}