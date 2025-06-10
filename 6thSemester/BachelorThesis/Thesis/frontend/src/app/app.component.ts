import {Component, HostListener} from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  standalone: false,
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'Integration Manager';
  /*@HostListener('window:beforeunload', ['$event'])
  clearLocalStorageOnUnload(event: Event) {
    localStorage.clear();
  }*/
}
