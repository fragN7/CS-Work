import {Injectable} from "@angular/core";
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Router} from "@angular/router";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})
export class AuthService {

  private url = 'http://localhost:5199/api/user/login';
  constructor(private http: HttpClient, private router: Router) { }

  login(username: string, password: string) : Observable<any> {

    const user = {
      username: username,
      password: password
    };

    const headers = new HttpHeaders({ 'Content-Type': 'application/json' });
    return this.http.post<any>(this.url, user, { headers });
  }

  logout() {
    localStorage.removeItem('user');
    localStorage.removeItem('token');
    this.router.navigateByUrl("/");
  }

  isLoggedIn(){
    return localStorage.getItem('user');
  }
}
