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

  login(username: string, password: string){
    return this.http.get<any>(`${this.URL}/login?username=${username}&password=${password}`);
  }
}
