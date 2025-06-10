import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PartnerDeclarationComponent } from './partner-declaration.component';

describe('PartnerDeclarationComponent', () => {
  let component: PartnerDeclarationComponent;
  let fixture: ComponentFixture<PartnerDeclarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [PartnerDeclarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(PartnerDeclarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
