import { Component } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";

@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {
  private URL = 'https://localhost:7074/api';
  constructor(private http: HttpClient, private router: Router) {}

  postGame(gameId: string, word: string, lives: number){
    return this.http.post<any>(`${this.URL}/game/${gameId}/${word}/${lives}`, null);
  }

  validateGame(gameId: string){
    return this.http.post<any>(`${this.URL}/validate/${gameId}`, null);
  }
}
