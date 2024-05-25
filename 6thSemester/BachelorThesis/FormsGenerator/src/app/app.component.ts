import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'FormsGenerator';
  fileContent: string = '';  //Asta e pentru continutul din preview input
  fileContent2: string = '';  //Asta pentru output

  selectedFile: File | null = null;

  onFileSelected(event: Event): void {
    const input = event.target as HTMLInputElement;
    if (input.files && input.files.length > 0) {
      this.selectedFile = input.files[0];
      if (this.selectedFile) {
        const reader = new FileReader();
        reader.onload = () => {
          this.fileContent = reader.result as string;
        };
        reader.readAsText(this.selectedFile);
      }
    }
  }
}
