import { Component } from '@angular/core';
import {Router} from "@angular/router";
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Observable, tap} from "rxjs";

@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {

  private URL = 'https://localhost:7020/api';
  constructor(private http: HttpClient, private router: Router) {}

  login(username: string, mother: string, father: string){
    return this.http.get<any>(`${this.URL}/login?username=${username}&mother=${mother}&father=${father}`);
  }

  add(mother: string, father: string): Observable<any> {
    let userId = parseInt(localStorage.getItem('userId')!);

    const body = {
      Mother: mother,
      Father: father,
      UserId: userId
    }

    return this.http.post<any>(`${this.URL}/add`, body);
  }

  getSiblings(){
    let userId = parseInt(localStorage.getItem('userId')!);
    return this.http.get<any[]>(`${this.URL}/siblings?userId=${userId}`);
  }

  getMothers(){
    let userId = parseInt(localStorage.getItem('userId')!);
    return this.http.get<any[]>(`${this.URL}/mothers?userId=${userId}`);
  }
  getFathers(){
    let userId = parseInt(localStorage.getItem('userId')!);
    return this.http.get<any[]>(`${this.URL}/fathers?userId=${userId}`);
  }


}
