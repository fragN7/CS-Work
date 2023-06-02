import {Component, OnInit} from '@angular/core';
import {Multimedia, ServiceComponent} from "../service/service.component";
import {Router} from "@angular/router";
@Component({
  selector: 'app-browse',
  templateUrl: './browse.component.html',
  styleUrls: ['./browse.component.css']
})

export class BrowseComponent implements OnInit{
  files: Multimedia[] = [];

  constructor(private service: ServiceComponent, private router: Router) { }

  ngOnInit() {
    this.browseFiles('all');
  }

  browseFiles(filterByGenre: string){
    this.service.getBrowsedFiles(filterByGenre).subscribe(
      (response: Multimedia[]) => {
        this.files = response;
      },
      (error: any) => {
        console.error('Error fetching browsed files: ', error);
      }
    );
  }

  deleteFile(id: number) {
    console.log(id);
    if (confirm('Are you sure you want to delete this multimedia file?')) {
      this.service.deleteFiles(id).subscribe(
        () => {
          // Reload the browse page to show the updated list of multimedia files
          this.browseFiles('all');
        },
        (error: any) => {
          console.error('Error deleting multimedia file: ', error);
        }
      );
    }
  }

  updateFile(id: number) {
    this.router.navigate(['/update', id]);
  }
}
