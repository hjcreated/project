//================ CHANGE COLOR OF NAVBAR ===========
/*
 this function is used to change the color of the navbar while scrolling up or down
 */
$(document).ready(function(){
    // language=JQuery-CSS
    $(function() {
        $(window).scroll(function () {
            if ($(this).scrollTop() > 50) {
                $("#nav").addClass("navbar navbar-expand-lg fixed-top");
                $("#nav").removeClass("navbar-expand-lg  navbar-transparent");
            }
            if ($(this).scrollTop() < 50) {
                $("#nav").removeClass(" navbar-expand-lg ");
                $("#nav").addClass("navbar navbar-expand-lg fixed-top navbar-transparent");
            }
        });
    });
});
//=========================== up button =======================
/* this is used to hide th up button at the beginning of the website
and show it back again when the first page has been exceeded.
 */
$(function () {
        $( '[id="upButton"]' ).hide();
    $(window).scroll(function () {
        if ($(this).scrollTop() > $("#firstPage").height()) {
            $('[id="upButton"]').show();}
        if ($(this).scrollTop() < $("#firstPage").height()) {
            $('[id="upButton"]').hide();}
    });

});
