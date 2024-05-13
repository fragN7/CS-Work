package org.example.steps.serenity;

import net.thucydides.core.annotations.Step;
import org.example.pages.ImdbPage;

import java.util.List;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsString;
import static org.hamcrest.Matchers.hasItem;
import static org.hamcrest.Matchers.isEmptyString;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.Matchers.equalTo;
public class EndUserStepsImdb {

    ImdbPage imdbPage;

    @Step
    public void enters(String keyword) {
        imdbPage.enter_keywords(keyword);
    }

    @Step
    public void starts_search() {
        imdbPage.lookup_data();
    }

    @Step
    public void is_the_home_page() {
        imdbPage.open();
    }
}
