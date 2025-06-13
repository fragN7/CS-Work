import {Component, OnDestroy, OnInit} from '@angular/core';
import {Partner, ServiceComponent} from '../../../../service/service.component';
import {AuthService} from '../../../../service/authentication/authentication.service';
import {Router} from '@angular/router';
import {CdkDragDrop, moveItemInArray, transferArrayItem} from '@angular/cdk/drag-drop';

@Component({
  selector: 'app-partner-declaration',
  standalone: false,
  templateUrl: './partner-declaration.component.html',
  styleUrl: './partner-declaration.component.css'
})
export class PartnerDeclarationComponent implements OnInit, OnDestroy{

  partner: Partner = { id: '', name: '', ipAddress: '', certificate: '' };
  certificate: File = null!;
  username?: string = '';

  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    const partnerId = localStorage.getItem('partnerId')?.toString();
    if(partnerId != null){
      this.getPartnerById(partnerId);
    }
    this.username = localStorage.getItem('user')?.toString();
  }

  ngOnDestroy() {
    localStorage.removeItem('partnerId');
    localStorage.removeItem('saveType');
  }
  getPartnerById(partnerId: string){
    this.service.getPartnerById(partnerId).subscribe(
      (response: Partner) => {
        this.partner = response;
      },
      (error: any) => {
        console.error('Error fetching partner: ', error);
      }
    )
  }

  userLogout(){
    this.userService.logout();
  }

  handleFileUpload(event: Event): void {
    const input = event.target as HTMLInputElement;
    if (input.files && input.files.length > 0) {
      const file = input.files![0];

      if (!file.name.toLowerCase().endsWith('.pem')) {
        alert('Only .pem files are allowed.');
        return;
      }

      this.certificate = file;
      this.partner.certificate = file.name;
    }
  }

  savePartner() {

    const type = localStorage.getItem('saveType');
    if(type == 'edit'){
      this.service.editPartner(localStorage.getItem('partnerId')!, this.partner.name, this.partner.ipAddress, this.partner.certificate, this.certificate);
    } else {
      this.service.addPartner(this.partner.name, this.partner.ipAddress, this.partner.certificate, this.certificate).subscribe(
        response => {
          console.log("Partner added successfully", response);
          this.service.addChannel(response.id.toString());
          this.router.navigateByUrl("/partners");
        },
        error => {
          console.error("Error while adding partner", error.error);

          let rawError = error.error;
          let message = '';

          if (typeof rawError === 'string') {
            const match = rawError.match(/System\.Exception:\s*(.*)/);
            if (match && match[1]) {
              message = match[1].split('\n')[0].trim();
            } else {
              message = rawError.split('\n')[0].trim();
            }
          } else {
            message = 'An unknown error occurred.';
          }

          alert(`Error while adding partner:\n${message}`);
        }
      );
    }
  }
}
