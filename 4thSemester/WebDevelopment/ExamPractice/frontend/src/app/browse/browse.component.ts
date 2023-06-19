import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})



export class BrowseComponent implements OnInit{

  authors = {
    firstAuthor: '',
    secondAuthor: ''
  }

  history: string[] = [];
  books: any[] = [];
  articles: any[] = [];
  constructor(private service: ServiceComponent, private route: Router) {}

  ngOnInit() {
    this.authors.firstAuthor = localStorage.getItem('firstAuthor')!;
    this.authors.secondAuthor = localStorage.getItem('secondAuthor')!;

    const storedHistory = localStorage.getItem('history');
    if (storedHistory) {
      this.history = JSON.parse(storedHistory);
    }

    if(this.authors.firstAuthor != '')
      this.history.push(this.authors.firstAuthor);

    if(this.authors.secondAuthor != '')
      this.history.push(this.authors.secondAuthor);

    localStorage.setItem('history', JSON.stringify(this.history));

    this.getBooksArticles();
  }

  getBooksArticles(){
    this.service.getBooksArticles(this.authors.firstAuthor, this.authors.secondAuthor).subscribe(
      (response: any) => {
        this.books = response.books;
        this.articles = response.articles;
      }, (error: any) => {
      alert(error.error);
    });
  }

  goBack(){
    localStorage.removeItem('firstAuthor');
    localStorage.removeItem('secondAuthor');
    this.route.navigateByUrl("/");
  }
}
