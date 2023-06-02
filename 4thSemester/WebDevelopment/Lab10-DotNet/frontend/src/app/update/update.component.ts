import {Component, OnInit} from '@angular/core';
import {ServiceComponent} from "../service/service.component";
import {ActivatedRoute} from "@angular/router";

@Component({
  selector: 'app-update',
  templateUrl: './update.component.html',
  styleUrls: ['./update.component.css']
})
export class UpdateComponent implements OnInit{

  file = {
    id: '',
    title: '',
    format: '',
    genre: '',
    path: ''
  };

  constructor(private route: ActivatedRoute, private service: ServiceComponent) {}

  ngOnInit() {
    this.route.paramMap.subscribe((params) => {
      const id = params.get('id');
      if (id) {
        this.file.id = id;
        this.service.getFile(id).subscribe(
          (data) => {
            this.file.title = data.title;
            this.file.format = data.format;
            this.file.genre = data.genre;
            this.file.path = data.path;
          },
          (error) => {
            console.error(error);
          }
        );
      }
    });
  }

  getFormat(event: any) {
    const dotPosition = event.lastIndexOf('.');
    if (dotPosition !== -1) {
      this.file.format = event.substring(dotPosition + 1);
    } else {
      this.file.format = '';
    }
  }

  updateFile() {
    const error = this.validateForm();
    if (error != '') {
      alert(error);
    }

    this.service.updateFiles(this.file.id, this.file.title, this.file.format, this.file.genre, this.file.path).subscribe(
      (response: any) => {
        console.log('File updated:', response);
        this.file = {
          id: '',
          title: '',
          format: '',
          genre: '',
          path: ''
        };
      },
      (error: any) => {
        console.error('Error updating file:', error);
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
