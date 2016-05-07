//2016.02 Conrad Schweiz
//header_hint -> initialise Footer Nav and ToTop Button
//Dev. Marie-Soizic Knarr
//v1.02
var $j = jQuery.noConflict();
var amountScrolled = 300;
var cchLanguage = configuration.language;
//console.log('Lang:' + cchLanguage);

function detectBrowserWidth() {
    if ($j(window).width() < 768) {
//        console.log('Browser less than 768. Lang:' + cchLanguage);
        return true;
    }
    else {
//        console.log('Browser more than 768. Lang:' + cchLanguage);
        return false;
    }
}


function setToTopBtn() {
    if (detectBrowserWidth()) {
// create the back to top button
        $j('body').prepend('<a href="#" class="back-to-top cch_mobile_display">Back to Top</a>');
//        console.log('Start To Top');


        $j(window).scroll(function () {
            if ($j(window).scrollTop() > amountScrolled) {
                $j('a.back-to-top').fadeIn('slow');
            } else {
                $j('a.back-to-top').fadeOut('slow');
            }
        });

        $j('a.back-to-top, a.simple-back-to-top').click(function () {
            $j('html, body').animate({
                scrollTop: 0
            }, 700);
            return false;
        });

    }
}


$j(document).ready(function () {
    if (detectBrowserWidth()) {
        if (cchLanguage === "de") {
            $j('body').append('<div id="cch_container_footer_mobile" class="cch_mobile_display test">' +
                    '<div id="cch_footer_btns">' +
                    '<a id="cch_btn_home" class="cch_footer_btn" href="/ce/de/Welcome.html?WT.ac=mobile_footernav_home"><div><i class="fa fa-home"></i><br />Home</div></a>' +
                    '<a id="cch_btn_kontakt" class="cch_footer_btn" href="/ce/de/ContactSend.html?WT.ac=footer_uberuns?WT.ac=mobile_footernav_kontakt"><i class="fa fa-envelope" ></i><br />Kontakt</a>' +
                    '<a id="cch_btn_impressum" class="cch_footer_btn" href="javascript:updateInfoCenter(\'info_delivery\');"><i class="fa fa-file-text-o"></i><br />Impressum</a>           ' +
                    '<div id="cch_btn_back">' +
                    '<button class="cch_footer_btn" onclick="history.go(-1);"><i class="fa fa-arrow-circle-left"></i><br />Zurück</button>' +
                    '</div>' +
                    '</div>' +
                    '</div>');
        } else if (cchLanguage === "it") {
            console.log('Test: Language IT');
            $j('body').append('<div id="cch_container_footer_mobile" class="cch_mobile_display test">' +
                    '<div id="cch_footer_btns">' +
                    '<a id="cch_btn_home" class="cch_footer_btn" href="/ce/it/Welcome.html?WT.ac=mobile_footernav_home"><div><i class="fa fa-home"></i><br />Home</div></a>' +
                    '<a id="cch_btn_kontakt" class="cch_footer_btn" href="/ce/it/ContactSend.html?WT.ac=footer_uberuns?WT.ac=mobile_footernav_kontakt"><i class="fa fa-envelope" ></i><br />Contatti</a>' +
                    '<a id="cch_btn_impressum" class="cch_footer_btn" href="javascript:updateInfoCenter(\'info_delivery\');"><i class="fa fa-file-text-o"></i><br />Condizioni</a>           ' +
                    '<div id="cch_btn_back">' +
                    '<button class="cch_footer_btn" onclick="history.go(-1);"><i class="fa fa-arrow-circle-left"></i><br />Indietro</button>' +
                    '</div>' +
                    '</div>' +
                    '</div>');
        }
    }
    setToTopBtn();
});