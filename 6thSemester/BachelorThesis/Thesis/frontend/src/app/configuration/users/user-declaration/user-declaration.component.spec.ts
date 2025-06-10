import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UserDeclarationComponent } from './user-declaration.component';

describe('UserDeclarationComponent', () => {
  let component: UserDeclarationComponent;
  let fixture: ComponentFixture<UserDeclarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [UserDeclarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(UserDeclarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
