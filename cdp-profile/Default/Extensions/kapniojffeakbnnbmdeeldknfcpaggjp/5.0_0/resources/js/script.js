/**
  * All in one Web Searcher
  * Main JS file for the extension popup
  * Author: Aakash Chakravarthy (https://www.aakashweb.com)
  * Version: 4.1
  **/

initOptions();

$(document).ready(function(){
    
    var selMethod = localStorage['ainows_tabSelection'];
    
    // Render the main tabs
    for (var key in searchEngines) {
        var obj = searchEngines[key];
        var subSearch = '';
        
        // Render the sub searches
        for (var prop in obj['sub']) {
            subSearch += '<li data-url="' + obj['sub'][prop] + '" title="' + prop + '">' + prop + '</li>';
        }
        if(!subSearch == '')
            subSearch = '<ul class="subWrap clearfix">' + subSearch + '</ul>';
        
        if(obj['icon'].trim() == ''){
            obj['icon'] = 'resources/images/blank.svg'
        }

        image = '<img src="resources/images/blank.svg" data-src="' + obj['icon'] + '"/>';
        $('#main').append('<li data-url="' + obj['url'] + '" title="' + key + '">' + image + subSearch + '</li>');
       
    }
    
    // Main tab on clicked
    $('#main>li').on(selMethod, function(){
        selectTab(this);
    }).children('.subWrap').on(selMethod, function(e) {
        return false;
    });
    
    // Sub tab on clicked
    $('.subWrap li').on(selMethod, function(){
        $('.subWrap li').removeClass('selSubTab');
        $(this).addClass('selSubTab');
        setUrl();
    });
    
    // Search button on click
    $('#searchBtn').on('click', function(e){
        e.preventDefault();
        openLink();
    });
    
    // Options page button
    $('#optionsBtn').on('click', function(e){
        e.preventDefault();
        chrome.runtime.openOptionsPage();
    });
    
    if( localStorage['ainows_theme'] ){
        $('body').addClass( localStorage['ainows_theme'] + '-theme' );
    }
    
    // Run the init function
    formInit();
    
});

$(document).on('keydown', function(e) {
    
    if (e.key == 'Enter'){
        e.preventDefault();
        openLink();
    }
    
     if (e.key == 'Tab') {
        e.preventDefault();
        $next = $('.selMainTab').next();
        if($next.length == 0){
            selectTab($('#main>li:first'));
        }else{
            selectTab($next);
        }
    }
    
    if (e.altKey) {
        e.preventDefault();
        $next = $('.selSubTab').next();
        
        $('#main>li .subWrap li').removeClass('selSubTab');

        if($next.length == 0){
            $('.selMainTab .subWrap li:first').addClass('selSubTab');
            setUrl()
        }else{
            $next.addClass('selSubTab');
            setUrl()
        }
    }
    
});

// Initializations
function formInit(){
    // Focus hack
    if (location.search != "?focusHack") location.search = "?focusHack";
    
    // Select the first tab
    selectTab($('#main>li:first'));
    
    setTimeout(function(){
        $('#main img').each(function(){
            $(this).attr('src', $(this).attr('data-src'));
            $(this).fadeTo('slow', 1);
        });
    }, 100);
    
    if(localStorage['ainows_saveSearchTerm'] == 1){
        $('#searchBox').val(localStorage['ainows_searchTerm'])
    }
    
}

// Tabs on clicked
function selectTab(tab){
    $('#main>li').removeClass('selMainTab');
    $('#main>li .subWrap').hide();
    $('#main>li .subWrap li').removeClass('selSubTab');
    
    $(tab).addClass('selMainTab');
    $(tab).children('.subWrap').show();
    $(tab).find('.subWrap li:first').addClass('selSubTab');
    
    // Set the URL after the click action
    setUrl();
}

// Open the search link
function openLink(){
    var searchTxt = $('#searchBox').val();
    var searchUrl = $('#searchUrl').val();
    
    if(searchTxt == '') return '';

    localStorage['ainows_searchTerm'] = (localStorage['ainows_saveSearchTerm'] == 1) ? searchTxt : '';

    selectedUrl = searchUrl.replace('%s', encodeURIComponent(searchTxt));

    if(localStorage['ainows_openIn'] == 'new'){
        chrome.tabs.create({
            'url': selectedUrl
        });
    }else{
        chrome.tabs.update({
            'url': selectedUrl
        });
    }

}

// Get the current search URL based on the tab selection.
function setUrl(){
    if($('.selMainTab .subWrap').length == 0){
        $('#searchUrl').val($('.selMainTab').attr('data-url'));
    }else{
        $('#searchUrl').val($('.selSubTab').attr('data-url'));
    }
    $('#searchBox').focus();
}

// Set the default options
function initOptions(){
    var gi = function(data){
        return localStorage.getItem(data);
    }
    
    var si = function(data, val){
        localStorage.setItem(data, val);
    }
    
    if(gi('ainows_saveSearchTerm') === null) {si('ainows_saveSearchTerm', 0);}
    if(gi('ainows_tabSelection') === null) {si('ainows_tabSelection', 'mouseover');}
    if(gi('ainows_theme') === null) {si('ainows_theme', 'light');}
    if(gi('ainows_openIn') === null) {si('ainows_openIn', 'new');}

}