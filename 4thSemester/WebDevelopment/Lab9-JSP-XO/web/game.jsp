<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Game</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <style>
        body {
            padding: 20px;
        }

        .cell {
            width: 80px;
            height: 80px;
            font-size: 24px;
            text-align: center;
            border: 1px solid #ccc;
            cursor: pointer;
        }
    </style>
</head>
<body>
<div class="container">
    <h1 class="mt-5">X-O Game</h1>
    <p class="lead mt-4">Welcome, <%= session.getAttribute("username") %>!</p>

    <h3 class="mt-5">Game Board</h3>
    <table class="table table-bordered mt-3">
        <tr>
            <td class="cell">X</td>
            <td class="cell">O</td>
            <td class="cell">X</td>
        </tr>
        <tr>
            <td class="cell">O</td>
            <td class="cell">X</td>
            <td class="cell">O</td>
        </tr>
        <tr>
            <td class="cell">X</td>
            <td class="cell">O</td>
            <td class="cell">X</td>
        </tr>
    </table>

    <form method="post" action="game">
        <p class="mt-4">Select a cell:</p>
        <input type="text" name="cell" class="form-control">
        <button type="submit" class="btn btn-primary mt-3">Submit</button>
    </form>

    <a class="btn btn-secondary mt-3" href="logout">Logout</a>
</div>

<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>
