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

  private browseURL = 'http://localhost/WebLab/browse.php';
  private getFilesURL = 'http://localhost/WebLab/getFiles.php';
  private addFilesURL = 'http://localhost/WebLab/add.php';
  private updateFilesURL = 'http://localhost/WebLab/update.php';
  private deleteFilesURL = 'http://localhost/WebLab/delete.php';
  constructor(private http: HttpClient, private router: Router) { }
  getBrowsedFiles(filterByGenre: string) : Observable<any> {
    const params = {
      filter_by_genre: filterByGenre
    };

    return this.http.get<Multimedia[]>(this.browseURL, { params: params });
  }

  getFile(id: string): Observable<any> {
    const params = {
      id: id
    };

    return this.http.get<Multimedia>(this.getFilesURL, {params: params});
  }

  addFiles(title: string, format: string, genre: string, path: string): Observable<any> {

    const body = new FormData();
    body.append("Title", title.toString());
    body.append("Format", format.toString());
    body.append("Genre", genre.toString());
    body.append("Path", path.toString());

    return this.http.post<Multimedia>(this.addFilesURL, body).pipe(
      tap(() => {
        alert("File has been added.");
        this.router.navigate(['/']);
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

    return this.http.post<any>(this.updateFilesURL, body).pipe(
      tap(() => {
        alert("File has been updated.");
        this.router.navigate(['/']);
      })
    );
  }

  deleteFiles(id: number): Observable<any> {
    const body = new FormData();
    body.append('id', id.toString());

    return this.http.post<Multimedia>(this.deleteFilesURL, body);
  }
}
