import {Component, OnChanges, OnInit, SimpleChanges} from '@angular/core';
import {ServiceComponent} from "../service/service.component";

@Component({
  selector: 'app-add',
  templateUrl: 'add.component.html',
  styleUrls: ['add.component.css']
})
export class AddComponent implements OnInit {
  file = {
    title: '',
    format: '',
    genre: '',
    path: ''
  };

  constructor(private service: ServiceComponent) {}

  ngOnInit() {}


  /*ngOnChanges(changes: SimpleChanges) {
    if (changes['file'] && changes['file'].currentValue && changes['file'].currentValue['path']) {
      const pathValue = this['file']['path'];
      console.log(pathValue);
      const dotPosition = pathValue.lastIndexOf('.');
      if (dotPosition !== -1) {
        const substringAfterDot = pathValue.substring(dotPosition + 1);
        this['file']['format'] = substringAfterDot;
        console.log(substringAfterDot);
      }
    }
  }*/

  getFormat() {
    const pathValue = this.file.path;
    console.log(pathValue);

    const dotPosition = pathValue.lastIndexOf('.');
    if (dotPosition !== -1) {
      const substringAfterDot = pathValue.substring(dotPosition + 1);
      this.file.format = substringAfterDot;
    }
    return this.file.format;

    /*const dotPosition = this.file.path.lastIndexOf('.');
    if (dotPosition !== -1) {
      const substringAfterDot = this.file.path.substring(dotPosition + 1);
      this.file.format = substringAfterDot;
    } else {
      this.file.format = '';
    }*/
  }

  addFile() {
    const error = this.validateForm();
    if (error != '') {
      alert(error); // Stop execution if form validation fails
    }

    this.service.addFiles(this.file.title, this.file.format, this.file.genre, this.file.path).subscribe(
      (response: any) => {
        console.log('File added:', response);
        this.file = {
          title: '',
          format: '',
          genre: '',
          path: ''
        };
      },
      (error: any) => {
        // Handle error
        console.error('Error adding file:', error);
      }
    );
  }

  validateForm(): string {
    const { title, format, genre, path } = this.file;
    let errors = '';

    if (!title) {
      errors += 'Title is required.';
    }

    if (!format) {
      errors += 'Format is required.';
    }

    if (!genre) {
      errors += 'Genre is required.';
    }

    if (!path) {
      errors += 'Path is required.';
    } else {
      const dotPosition = path.lastIndexOf('.');
      if (dotPosition !== -1) {
        const substringAfterDot = path.slice(dotPosition + 1);

        if (substringAfterDot !== format) {
          errors += 'The format does not match the file extension in the path.';
        }
      } else {
        errors += 'Invalid path.';
      }
    }

    return errors;
  }

}
