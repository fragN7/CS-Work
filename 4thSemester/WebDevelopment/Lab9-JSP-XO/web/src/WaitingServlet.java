import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/waiting")
public class WaitingServlet extends HttpServlet {

    private static List<String> players = new ArrayList<>();

    public static List<String> getPlayers() {
        return players;
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (players.size() >= 2) {
            response.sendRedirect("game.jsp");
        } else {
            request.getRequestDispatcher("waiting.jsp").forward(request, response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = (String) request.getSession().getAttribute("username");
        players.add(username);

        response.sendRedirect("waiting");
    }
}
