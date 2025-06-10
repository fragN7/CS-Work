import {Component, OnDestroy, OnInit} from '@angular/core';
import {ServiceComponent} from '../../../service/service.component';
import {AuthService} from '../../../service/authentication/authentication.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-certificate-declaration',
  standalone: false,
  templateUrl: './certificate-declaration.component.html',
  styleUrl: './certificate-declaration.component.css'
})
export class CertificateDeclarationComponent implements OnInit{

  username?: string = '';
  certificate = {
    sender: '',
    receiver: '',
    standard: '',
    hostName: '',
    port: ''
  }
  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }

  ngOnInit() {
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout(){
    this.userService.logout();
  }

  saveCertificate(){
    this.service.generateCertificate(this.certificate.sender, this.certificate.receiver, this.certificate.standard, this.certificate.hostName, this.certificate.port).subscribe(
      response => {
        console.log("Certificate generated successfully", response);
        const certificate = {
          sender: response.sender,
          receiver: response.receiver,
          standard: response.standard,
          hostName: response.hostName,
          port: response.port,
          password: response.password ?? "WARNING"
        };

        const fileName = `${certificate.sender}_${certificate.receiver}.pem`;
        const json = JSON.stringify(certificate, null, 2);
        const blob = new Blob([json], { type: "application/json" });
        const url = URL.createObjectURL(blob);

        const a = document.createElement("a");
        a.href = url;
        a.download = fileName;
        a.click();

        URL.revokeObjectURL(url); // cleanup

        console.log("Certificate generated and downloaded successfully");

        this.router.navigateByUrl(`partner/create`);

      },
      error => {
        console.error("Error while generating certificate", error);
      }
    );
  }

}
