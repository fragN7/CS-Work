import { Component } from '@angular/core';
import {HttpClient, HttpHeaders} from "@angular/common/http";
import {Observable, tap} from "rxjs";
import {Router} from "@angular/router";

export interface Multimedia {
  id: number;
  title: string;
  format: string;
  genre: string;
  path: string;
}


@Component({
  selector: 'app-service',
  templateUrl: './service.component.html',
  styleUrls: ['./service.component.css']
})
export class ServiceComponent {

  private baseURL = 'http://localhost:5199/api/files';

  constructor(private http: HttpClient, private router: Router) { }
  getBrowsedFiles(filterByGenre: string) {
    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any[]>(`${this.baseURL}/genre/${filterByGenre}`, {headers});
  }

  getFile(id: string): Observable<any> {

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.get<any>(`${this.baseURL}/${id}`, {headers});
  }

  addFiles(title: string, format: string, genre: string, path: string): Observable<any> {

    const body = {
      'title': title,
      'format': format,
      'genre': genre,
      'path': path
    };

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.post<any>(this.baseURL, body, {headers}).pipe(
      tap(() => {
        alert("File has been added.");
        this.router.navigate(['/browse']);
      })
    );
  }
  updateFiles(id: string, title: string, format: string, genre: string, path: string) {

    const body = {
      'id': id,
      'title': title,
      'format': format,
      'genre': genre,
      'path': path
    };

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.put<any>(`${this.baseURL}/${id}`, body, {headers}).pipe(
      tap(() => {
        alert("File has been updated.");
        this.router.navigate(['/browse']);
      })
    );
  }

  deleteFiles(id: number): Observable<any> {

    const token = localStorage.getItem('token');
    const headers = new HttpHeaders()
      .append('Authorization', `Bearer ${token}`)
      .append('Content-Type', 'application/json');

    return this.http.delete<any>(`${this.baseURL}/${id}`, {headers});
  }
}
