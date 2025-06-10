import { ComponentFixture, TestBed } from '@angular/core/testing';

import { MessageProcessingComponent } from './message-processing.component';

describe('MessageProcessingComponent', () => {
  let component: MessageProcessingComponent;
  let fixture: ComponentFixture<MessageProcessingComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [MessageProcessingComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(MessageProcessingComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
