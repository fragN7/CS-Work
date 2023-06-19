import { Component } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Router} from "@angular/router";

@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {

  private URL = 'https://localhost:7023/api';

  constructor(private http: HttpClient, private router: Router) {}

  getBooksArticles(firstAuthor: string, secondAuthor: string){
    if(firstAuthor == '')
      return this.http.get<any>(`${this.URL}?firstAuthor=${secondAuthor}&secondAuthor=${firstAuthor}`);
    return this.http.get<any>(`${this.URL}?firstAuthor=${firstAuthor}&secondAuthor=${secondAuthor}`);
  }
}
