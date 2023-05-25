<?php
// Connect to the database
$con = new mysqli("localhost", "root", "", "multimedia_files");

header("Access-Control-Allow-Origin: http://localhost:4200");
header("Access-Control-Allow-Methods: GET, POST, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");


// Retrieve the data based on the selected option and value
if (isset($_GET['filter_by_genre'])) {
    $filterByGenre = $_GET['filter_by_genre'];

    // Sanitize user input to prevent SQL injection
    $filterByGenre = mysqli_real_escape_string($con, $filterByGenre);

    // Build the SQL query with the WHERE clause based on the selected options
    $whereClause = '';

    if (!empty($filterByGenre)) {
        $whereClause .= "genre LIKE '%$filterByGenre%'";
    }

    $sql = "SELECT * FROM multimedia_file";

    if (!empty($whereClause)) {
        $sql .= " WHERE $whereClause";
    }

    // Execute the query and fetch the results
    $result = $con->query($sql);
    $data = array();
    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    // Return the results as a JSON response
    if (!empty($data)) {
        echo json_encode($data);
    } else {
        echo "No records found.";
    }
}

// Close the database
