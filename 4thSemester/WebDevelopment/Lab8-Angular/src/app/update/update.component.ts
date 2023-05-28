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
            console.log(data);
            this.file.title = data[0].title;
            this.file.format = data[0].format;
            this.file.genre = data[0].genre;
            this.file.path = data[0].path;
          },
          (error) => {
            console.error(error);
          }
        );
      }
    });
  }

  getFormat() {
    const pathValue = this.file.path;

    const dotPosition = pathValue.lastIndexOf('.');
    if (dotPosition !== -1) {
      const substringAfterDot = pathValue.substring(dotPosition + 1);
      this.file.format = substringAfterDot;
    }
    return this.file.format;
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
