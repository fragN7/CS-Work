import { Component } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";

@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {

  private URL = 'https://localhost:7077/api';
  constructor(private http: HttpClient, private router: Router) {}

  login(username: string){
    return this.http.get<any>(`${this.URL}/login?username=${username}`);
  }
  loginSecurity(username: string, answer: string){
    return this.http.get<any>(`${this.URL}/security?username=${username}&answer=${answer}`);
  }
  getMessages(username: string){
    return this.http.get<any[]>(`${this.URL}/messages?username=${username}`);
  }

  sendMessage(username: string, message: string, receiver:string){
    return this.http.post<any[]>(`${this.URL}/send/${username}/${message}/${receiver}`, null);
  }

  deleteMessage(receiver: string){
    return this.http.get<any>(`${this.URL}/remove/${receiver}`);
  }

}
