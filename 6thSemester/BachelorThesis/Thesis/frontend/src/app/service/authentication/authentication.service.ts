import {Injectable} from "@angular/core";
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Router} from "@angular/router";
import {Observable} from "rxjs";

@Injectable({
  providedIn: 'root'
})

export class AuthService {

  constructor(private http: HttpClient, private router: Router) { }

  login(userName: string, password: string, hostName: string, port: string) : Observable<any> {
    const user = {
      userName: userName,
      password: password
    };

    const headers = new HttpHeaders({ 'Content-Type': 'application/json' });
    return this.http.post<any>(`https:/${hostName}:${port}/api/Authentication/login`, user, { headers });
  }

  isLoggedIn(){
    return localStorage.getItem('user');
  }

  logout(){
    localStorage.removeItem('user');
    localStorage.removeItem('token');
    localStorage.removeItem('userId');
    localStorage.removeItem('myURL');
    this.router.navigate(['/login']);
  }
}
