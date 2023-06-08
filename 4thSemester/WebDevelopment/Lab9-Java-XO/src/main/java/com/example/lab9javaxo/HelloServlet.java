package com.example.lab9javaxo;

import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

@WebServlet(name = "HelloServlet", value = "/hello-servlet")
public class HelloServlet extends HttpServlet {
    private String message;
    Connection connection = null;
    String url = "jdbc:postgresql://localhost:5432/webdotnet";
    String username = "postgres";
    String password = "rootroot";

    public void init() {
        message = "Hello World!";
        /*System.out.println("Starting to connect database!");
        try {
            connection = DriverManager.getConnection(url, username, password);
            System.out.println("Connected to the PostgreSQL database!");
            message += " Connected";
        } catch (SQLException ex) {
            System.out.println("Failed to connect to the PostgreSQL database!");
            message += " Failed";
            ex.printStackTrace();
        }
        finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }*/
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");

        // Hello
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>" + message + "</h1>");
        out.println("</body></html>");
    }

    public void destroy() {
    }
}