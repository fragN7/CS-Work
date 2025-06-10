import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RuleDeclarationComponent } from './rule-declaration.component';

describe('RuleDeclarationComponent', () => {
  let component: RuleDeclarationComponent;
  let fixture: ComponentFixture<RuleDeclarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [RuleDeclarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(RuleDeclarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
