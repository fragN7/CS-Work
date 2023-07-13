import { Component } from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.css']
})
export class MainComponent {
  gameId: string = '';
  word: string = '';
  lives: number = 0;
  dialogVisible: boolean = false;

  constructor(private service: ServiceComponent, private router: Router) { }

  openDialog(): void {
    this.dialogVisible = true;
  }

  closeDialog(): void {
    this.dialogVisible = false;
  }

  saveGame(): void {

    localStorage.setItem('word', this.word.toUpperCase());
    localStorage.setItem('lives', this.lives.toString());

    this.service.postGame(this.gameId, this.word, this.lives).subscribe(
      (response: any) => {
        alert(`Created game`);
        this.router.navigateByUrl(`/game/${this.gameId}`);
      },
      (error: any) => {
        alert(error.error);
      }
    );

    // Close the dialog
    this.closeDialog();
  }
}
