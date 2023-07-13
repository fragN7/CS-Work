import {ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";
import {Component, HostListener, OnInit} from "@angular/core";

@Component({
  selector: 'app-game',
  templateUrl: './game.component.html',
  styleUrls: ['./game.component.css']
})
export class GameComponent implements OnInit {
  word: string = '';
  lives: number = 0;
  characters: string = '';
  gameId: string = '';
  underscores: string = '';
  letters: number = 0;
  alphabet: { letter: string, style: string }[] = [];

  revealedLetters: string[] = [];
  usedLetters: string[] = [];
  constructor(private service: ServiceComponent, private route: Router) {}

  ngOnInit() {
    const url = window.location.href;
    this.gameId = url.split('/game/')[1];
    this.initializeAlphabet();
    const savedGameState = localStorage.getItem('gameState');

    if (savedGameState) {
      const gameState = JSON.parse(savedGameState);
      this.revealedLetters = gameState.revealedLetters;
      this.usedLetters = gameState.usedLetters;
      this.underscores = gameState.underscores;
      this.alphabet = gameState.alphabet;
      this.lives = gameState.lives;
    }
    else {
      this.validate();
    }

    this.letters = this.underscores.length;
  }

  validate() {
    this.service.validateGame(this.gameId).subscribe(
      (response: any) => {
        this.word = response.word;
        this.letters = response.word.length;
        this.lives = response.lives;
        this.characters = this.word.toString();
        this.generateUnderscores();
      },
      (error: any) => {
        alert(error.error);
        this.route.navigateByUrl('/');
      }
    );
  }

  initializeAlphabet() {
    for (let i = 65; i <= 90; i++) {
      this.alphabet.push({ letter: String.fromCharCode(i), style: '' });
    }
  }

  generateUnderscores() {
    this.underscores = '_'.repeat(this.characters.length);
  }

  saveGameState() {
    localStorage.setItem('gameState', JSON.stringify({
      revealedLetters: this.revealedLetters,
      usedLetters: this.usedLetters,
      underscores: this.underscores,
      alphabet: this.alphabet,
      lives: this.lives
    }));
  }

  onClickLetter(letter: string) {
    const letterIndex = this.word.indexOf(letter);
    const isCorrectLetter = letterIndex !== -1;

    if (isCorrectLetter) {
      this.revealLetter(letter);
      this.setStyle(letter, 'green');
    } else {
      this.updateLives();
      this.setStyle(letter, 'red');
    }

    this.disableButton(letter);
    this.saveGameState();
  }

  setStyle(letter: string, color: string) {
    const button = this.alphabet.find(item => item.letter === letter);
    if (button) {
      button.style = color;
    }
  }

  revealLetter(letter: string) {
    const revealedWord = this.underscores.split('');

    for (let i = 0; i < this.word.length; i++) {
      if (this.word[i] === letter) {
        revealedWord[i] = letter;
      }
    }

    this.underscores = revealedWord.join('');
  }

  updateLives() {
    this.lives--;
  }

  disableButton(letter: string) {
    this.usedLetters.push(letter);
  }
}
