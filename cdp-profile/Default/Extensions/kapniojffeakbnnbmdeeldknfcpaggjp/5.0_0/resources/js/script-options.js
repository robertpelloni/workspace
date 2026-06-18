$(document).ready(function(){
    
    // Elements
    var mainItem = function(name, url, icon, sWrap){
        return '<li><img src="../resources/images/drag.svg" title="Rearrange" class="mDragBt" /><img src="../resources/images/remove.svg" title="Remove" class="mRemBt" /><img src="../resources/images/add-sub.svg" title="Add sub search URLs" class="sAddBt sAddGrpBt" /><img src="../resources/images/add.svg" title="Add a new search URL" class="mAddBt" /><input type="text" class="mName" placeholder="Name" value="' + name + '" /><input type="text" placeholder="Search URL" class="mUrl" value="' + url + '"/><input type="text" placeholder="Icon URL" class="mIcon" value="' + icon + '"/><ul class="subWrap">' + sWrap + '</ul></li>';
    };
    
    var subItem = function(name, url){
        return '<li><input type="text" placeholder="Name" class="sName" value="' + name + '"/><input type="text" placeholder="Search URL" class="sUrl" value="' + url + '"/><img src="../resources/images/add.svg" title="Add new sub search" class="sAddBt" /><img src="../resources/images/remove.svg" title="Remove" class="sRemBt" /><img src="../resources/images/drag.svg" title="Rearrange" class="sDragBt" /></li>';
    };
    
    restoreOptions();
    
    $('#save').click(function(){
        saveOptions();
    });
    
    $('#reset').click(function(){
        resetOptions();
    });
    
    $('#import').click(function(){
        importSettings();
    });
    
    $('#export').click(function(){
        exportSettings();
    });
    
    $(document).on('change blur', '.mUrl', function(){
        $icon = $(this).siblings('.mIcon');
        if($icon.val() == ''){
            $icon.fadeOut('fast');
            $icon.val(getBaseUrl($(this).val()) + 'favicon.ico');
            $icon.fadeIn('fast');
        }
    });
    
    // Render the Search engines
    for (var key in searchEngines) {
        var obj = searchEngines[key];
        
        // Sub details
        var ssWrap = '';
        for (var prop in obj['sub']) {
            ssWrap += subItem(prop, obj['sub'][prop]);
        }
        
        // Main details
        mainWrap = mainItem(key, obj['url'], obj['icon'], ssWrap);
        
        // Append the items
        $('.seList').append(mainWrap);
    }
    
    // Hide add sub searches if the subWrap is not empty
    $('.seList>li').each(function(){
        if(!$(this).children('.subWrap').is(':empty')){
            $(this).children('.sAddBt').hide();
            $(this).children('.mUrl').hide();
        }
    });
    
    $('.seList').sortable({
        handle: '.mDragBt'
    });
    
    $('.subWrap').sortable({
        handle: '.sDragBt',
        connectWith: '.subWrap'
    });
    
    // Actions
    $(document).on('click', '.mAddBt', function(){
        temp = mainItem('', '', '', '');				
        if($(this).hasClass('mAddGrpBt')){
            $('.seList').append(temp);
        }else{
            $(this).parent().after(temp);
        }
        
    });
    $(document).on('click', '.mRemBt', function(){
        res = confirm('Are you sure want to remove this ?');
        if(res == 1){
            $(this).parent().slideUp('slow', function(){
                $(this).remove();
            })
        }
    });
    
    $(document).on('click', '.sAddBt', function(){
        temp = subItem('', '');
        
        if($(this).hasClass('sAddGrpBt')){
            $(this).siblings('.subWrap').append(temp);
            $(this).siblings('.mUrl').fadeOut();
            $(this).hide();
        }else{
            $(this).parent().after(temp);
        }
        
    });
    
    $(document).on('click', '.sRemBt', function(){
        $subwrap = $(this).parent().parent();
        $(this).parent().fadeOut('fast', function(){
            $(this).remove(); 
            if($subwrap.is(':empty') == 1){
                $subwrap.siblings('.sAddBt').show();
                $subwrap.siblings('.mUrl').fadeIn();
            }
        });
    });
    
    $( '#exptCnt' ).on('mouseup',function(){
        $(this).select();
    });
    
});

function restoreOptions(){
    if(localStorage['ainows_saveSearchTerm'] == 1){
        $('#ainows_saveSearchTerm option[value=1]').attr('selected', 'selected');
    }
    
    if(localStorage['ainows_tabSelection'] == 'click'){
        $('#ainows_tabSelection option[value=click]').attr('selected', 'selected');
    }
    
    $('#ainows_theme option[value="' + localStorage['ainows_theme'] + '"]').attr('selected', 'selected');
    
    $('#ainows_openIn option[value="' + localStorage['ainows_openIn'] + '"]').attr('selected', 'selected');
}

function resetOptions(){
    
    if(confirm('Are you sure want to reset the options ?')){
        localStorage['ainows_saveSearchTerm'] = 0;
        localStorage['ainows_tabSelection'] = 'mouseover';
        localStorage['aiows_searchEngines'] = '';
        localStorage['ainows_theme'] = 'light';
        localStorage['ainows_openIn'] = 'new';
        document.location.reload();
    }
}

function saveOptions(){
    localStorage['ainows_saveSearchTerm'] = $('#ainows_saveSearchTerm').val();
    localStorage['ainows_tabSelection'] = $('#ainows_tabSelection').val();
    localStorage['ainows_theme'] = $('#ainows_theme').val();
    localStorage['ainows_openIn'] = $('#ainows_openIn').val();
    
    if(localStorage['ainows_saveSearchTerm'] == 0){
        localStorage['ainows_searchTerm'] = '';
    }
    storeObject();
}

function storeObject(){ 
    var tsengines = {};
    $('.seList>li').each(function(){
        var tempSub = {};
        if(!$(this).find('.subWrap').is(':empty')){
            $(this).find('.subWrap>li').each(function(){
                tempSub[$(this).find('.sName').val()] = $(this).find('.sUrl').val();
            });
        }
        
        key = $(this).find('.mName').val();
        tsengines[key] = {};
        tsengines[key]['icon'] = $(this).find('.mIcon').val();
        tsengines[key]['url'] = $(this).find('.mUrl').val();
        tsengines[key]['sub'] = tempSub;
        
    });
    
    localStorage.setItem('aiows_searchEngines', JSON.stringify(tsengines));
    
    $('.saveInfo').fadeIn('fast', function(){
        setTimeout(function(){
            document.location.reload();
        }, 1000);
    });
}

function getBaseUrl( url ) {
    if (url.indexOf('.') == -1 || url.indexOf('/') == -1){ 
        return '';
    }

    var result = url.substr(0, url.indexOf( '/' , url.indexOf('.') ) + 1 );
    return(result);
}

function importSettings(){
    var data = prompt( 'Paste the exported text from All In One Web Searcher' );
    
    if( data == null || data == '' ){
        return false;
    }else{
        
        localStorage.setItem('aiows_searchEngines', data );
        location.reload();
    }
}

function exportSettings(){
    var engs = localStorage['aiows_searchEngines'];
    
    if( engs == '' || engs == null ){
        alert('There is nothing to export !! Please save the settings.' );
    }else{
        
        $('.exptBox').fadeIn('slow');
        $('#exptCnt').html(engs);
        
    }
    
}