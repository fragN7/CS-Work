package org.example.pages;

import lombok.var;
import net.thucydides.core.annotations.DefaultUrl;
import org.openqa.selenium.By;
import net.serenitybdd.core.pages.WebElementFacade;
import java.util.stream.Collectors;

import net.serenitybdd.core.annotations.findby.FindBy;

import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.WebElement;

import java.util.List;


@DefaultUrl("https://www.imdb.com/")
public class ImdbPage extends PageObject {
    @FindBy(id = "suggestion-search")
    private WebElementFacade searchOnImdb;

    @FindBy(id = "suggestion-search-button")
    private WebElementFacade lookupButton;


    public void enter_keywords(String keyword) {
        searchOnImdb.type(keyword);
    }

    public void lookup_data() {
        lookupButton.click();
    }


}
