import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MessageDeclarationComponent } from './message-declaration.component';

describe('MessageDeclarationComponent', () => {
  let component: MessageDeclarationComponent;
  let fixture: ComponentFixture<MessageDeclarationComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [MessageDeclarationComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(MessageDeclarationComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
