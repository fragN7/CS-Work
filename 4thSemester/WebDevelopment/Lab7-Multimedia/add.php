<?php
$con = new mysqli("localhost", "root", "", "multimedia_files");
header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");
$errors = array();


try {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $title = $_POST["Title"];
        $format = $_POST["Format"];
        $genre = $_POST["Genre"];
        $path = $_POST["Path"];

        // Perform validation
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
                $substringAfterDot = substr($path, $dotPosition + 1);

                if($substringAfterDot != $format)
                    $errors[] = 'The format does not match the file extension in the path.';

            } else {
                $errors[] = 'Invalid path.';
            }
        }

        if (empty($errors)) {
            $stmt = $con->prepare("INSERT INTO multimedia_file (title, format, genre, path) VALUES (?, ?, ?, ?)");
            $stmt->bind_param("ssss", $title, $format, $genre, $path);

            if ($stmt->execute()) {
                $stmt->close();
                mysqli_close($con);
                //header("Location: browse.html");
                exit();
            } else {
                printf("%d Row inserted.\n", mysqli_affected_rows($con));
            }

            $stmt->close();
        }
        else {
            // Display the errors
            foreach ($errors as $error) {
                echo $error . "<br>";
            }
            // Redirect to browse.html
            //header("Location: browse.html");
            exit();
        }
    }
} catch (Exception $e) {
    echo 'Caught exception: ', $e->getMessage(), "\n";
}

mysqli_close($con);
