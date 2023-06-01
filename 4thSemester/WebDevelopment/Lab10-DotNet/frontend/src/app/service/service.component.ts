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

    return this.http.get<any[]>(`${this.baseURL}/files/genre/${filterByGenre}`, {headers});
  }

  getFile(id: string): Observable<any> {
    const params = {
      id: id
    };

    return this.http.get<Multimedia>(this.baseURL, {params: params});
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

    return this.http.post<Multimedia>(this.baseURL, body, {headers}).pipe(
      tap(() => {
        alert("File has been added.");
        this.router.navigate(['/browse']);
      })
    );
  }
  updateFiles(id: string, title: string, format: string, genre: string, path: string) {

    console.log(title);
    console.log(id);

    const body = new FormData();
    body.append("Id", id.toString());
    body.append("Title", title.toString());
    body.append("Format", format.toString());
    body.append("Genre", genre.toString());
    body.append("Path", path.toString());

    return this.http.put<any>(`${this.baseURL}/${id}`, body).pipe(
      tap(() => {
        alert("File has been updated.");
        this.router.navigate(['/']);
      })
    );
  }

  deleteFiles(id: number): Observable<any> {
    const body = new FormData();
    body.append('id', id.toString());

    return this.http.delete<any>(`${this.baseURL}/${id}`);
  }
}
