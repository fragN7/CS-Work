import { Component, OnInit } from '@angular/core';
import { Partner, Rule, ServiceComponent } from '../../../../service/service.component';
import { AuthService } from '../../../../service/authentication/authentication.service';
import { Router } from '@angular/router';

interface PartnerUI extends Partner {
  selected?: boolean;
}

@Component({
  selector: 'app-partner',
  standalone: false,
  templateUrl: './partner.component.html',
  styleUrl: './partner.component.css'
})
export class PartnerComponent implements OnInit {
  partners: PartnerUI[] = [];
  username?: string = '';
  constructor(private service: ServiceComponent, private userService: AuthService, private router: Router) { }
  nameFilter: string = '';
  ipFilter: string = '';
  certFilter: string = '';

  get filteredPartners() {
    return this.partners.filter(p =>
      (!this.nameFilter || p.name?.toLowerCase().includes(this.nameFilter.toLowerCase())) &&
      (!this.ipFilter || p.ipAddress?.toLowerCase().includes(this.ipFilter.toLowerCase())) &&
      (!this.certFilter || p.certificate?.toLowerCase().includes(this.certFilter.toLowerCase()))
    );
  }

  ngOnInit() {
    this.getPartners();
    this.username = localStorage.getItem('user')?.toString();
  }

  userLogout() {
    this.userService.logout();
  }

  getPartners() {
    this.service.getPartners().subscribe(
      (response: PartnerUI[]) => {
        this.partners = response.map(pt => ({ ...pt, selected: false }));
      },
      (error: any) => {
        console.error('Error fetching partners: ', error);
      }
    )
  }

  getSelectedPartners(): Partner[] {
    return this.partners.filter(pt => pt.selected);
  }

  toggleSelect(partner: PartnerUI): void {
    partner.selected = !partner.selected;
  }

  canEdit(): boolean {
    return this.getSelectedPartners().length === 1;
  }

  canCopy(): boolean {
    return this.getSelectedPartners().length === 1;
  }

  canAssign(): boolean {
    return this.getSelectedPartners().length === 1;
  }

  canDelete(): boolean {
    return this.getSelectedPartners().length > 0;
  }

  createPartner(): void {
    this.router.navigateByUrl(`partner/create`);
  }

  editPartner(): void {
    const selected = this.getSelectedPartners();
    if (selected.length === 1) {
      this.router.navigateByUrl(`partner/configure/${selected[0].id}`);
      localStorage.setItem('partnerId', selected[0].id.toString());
      localStorage.setItem('saveType', 'edit');
    }
  }

  copyPartner(): void {
    const selected = this.getSelectedPartners();
    if (selected.length === 1) {
      this.router.navigateByUrl(`partner/create`);
      localStorage.setItem('partnerId', selected[0].id.toString());
      localStorage.setItem('saveType', 'copy');
    }
  }

  deletePartner(): void {
    const selected = this.getSelectedPartners();
    if (selected.length === 0) return;

    const confirmMsg =
      selected.length === 1
        ? `Are you sure you want to delete this partner and all it's communication channels?`
        : `Are you sure you want to delete ${selected.length} partners and all their communiction channels?`;

    if (window.confirm(confirmMsg)) {
      selected.forEach(partner => {
        this.service.deletePartner(partner.id).subscribe({
          next: () => {
            this.partners = this.partners.filter(wf => wf.id !== partner.id);
          },
          error: (err) => {
            console.error(`Failed to delete partner ${partner.id}`, err);
            alert('Partner in use, can not be deleted');
          }
        });
        this.service.deleteChannel(partner.name);
      });
    }
  }
}
