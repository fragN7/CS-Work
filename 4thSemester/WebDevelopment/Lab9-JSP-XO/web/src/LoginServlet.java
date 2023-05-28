import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Retrieve the username and password from the form
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Perform authentication logic here
        boolean isAuthenticated = authenticate(username, password);

        if (isAuthenticated) {
            // Store user information in session or cookie
            // For example, storing username in session:
            request.getSession().setAttribute("username", username);

            // Redirect to the waiting.jsp page or any other desired page
            response.sendRedirect("waiting.jsp");
        } else {
            // Authentication failed, redirect back to the login page with an error message
            response.sendRedirect("login.jsp?error=1");
        }
    }

    private boolean authenticate(String username, String password) {
        // Implement your authentication logic here
        // You can check the provided username and password against the database

        // For this example, let's assume the authentication is successful if the username is "admin" and the password is "password"
        return "admin".equals(username) && "password".equals(password);
    }
}
