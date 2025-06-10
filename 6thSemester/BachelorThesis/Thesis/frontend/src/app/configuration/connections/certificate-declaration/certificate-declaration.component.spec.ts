import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CertificateDeclaarationComponent } from './certificate-declaaration.component';

describe('CertificateDeclaarationComponent', () => {
  let component: CertificateDeclaarationComponent;
  let fixture: ComponentFixture<CertificateDeclaarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [CertificateDeclaarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(CertificateDeclaarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
