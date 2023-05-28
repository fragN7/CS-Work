<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="WaitingServlet" %>

<html>
<head>
    <title>Waiting</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <style>
        body {
            padding: 20px;
        }
    </style>
</head>
<body>
<div class="container">
    <h1 class="mt-5">Waiting for Players</h1>
    <div class="mt-4">
        <% List<String> players = WaitingServlet.getPlayers(); %>
        <% int numPlayers = Math.min(2, players.size()); %>
        <p class="lead">Players connected: <%= numPlayers %>/2</p>
    </div>

    <%-- Check if the number of players is less than 2 --%>
    <% if (numPlayers < 2) { %>
    <p class="mt-4">Waiting for another player to join...</p>
    <% } else { %>
    <p class="mt-4">Game can start now!</p>
    <a class="btn btn-primary" href="game.jsp">Start Game</a>
    <% } %>
</div>

<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>
