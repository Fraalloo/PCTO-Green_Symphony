$(document).ready(function(){
    Ae()

    // Toggle
    $(".nav-toggle").click(function(){
        $(".header .nav").slideToggle()
    })
    $(".header .nav a").click(function(){
        if($(window).width() < 768){
            $(".header .nav").slideToggle()
        }
    })
    $(window).scroll(function(){
        if($(this).scrollTop() > 100){
            $(".header").addClass("fixed")
        }else{
            $(".header").removeClass("fixed")
        }
    })

    // Scroll
    $("a").on("click",function(event){
        if($(this).hash !== ""){
            event.preventDefault()
            let hash = this.hash
            $("html,body").animate({
                scrollTop: $(hash).offset().top
            }, 800, function(){
                window.location.hash = hash
            })
        }
    })

    // Scorrimento immagini
    let index = 0
    const totalItems = $(".service-item").length
    const wHeight = $(window).height()

    $(".lightbox-img").css("max-height", wHeight + "px")

    $(".service-item-inner").click(function(){
        index = $(this).parent(".service-item").index()
        $(".lightbox").addClass("open")
        lightboxSlideShow()
    })

    $(".lightbox .prev").click(function(){
        if(index == 0){
            index = totalItems - 1
        }else{
            index--
        }
        lightboxSlideShow()
    })

    $(".lightbox .next").click(function(){
        if(index == totalItems - 1){
            index = 0
        }
        else{
            index++
        }
        lightboxSlideShow()
    })

    $(".lightbox-close").click(function(){
        $(".lightbox").removeClass("open")
    })

    $(".lightbox").click(function(event){
        if($(event.target).hasClass("lightbox")){
            $(this).removeClass("open")
        }
    })

    function lightboxSlideShow(){
        let desc = [
            "Il Tech Flora v1 ti aiuta a tenere sotto controllo la tua pianta, misurando l'umidità, luminosità e temperatura e tutto questo da remoto",
            "Il Tech Flora fdt1 ti permette di sviluppare da solo il tuo vaso tecnologico e a casa arriveranno i componenti e un libricino illustrativo, per aiutarti nel processo.",
            "Nuovi prodotti arriveranno prossimamente."
        ]
        let imgSrc = $(".service-item").eq(index).find("img").attr("data-large")
        let category = $(".service-item").eq(index).find("h3").html()
        $(".lightbox-img").attr("src", imgSrc)
        $(".lightbox-category").html(category)
        $(".lightbox-description").html(desc[index])
        $(".lightbox-counter p").html((index + 1)+ "/" + totalItems)
    }// Il Tech Flora v1 ti aiuta a tenere sotto controllo la tua pianta, misurando l'umidità, luminosità e temperatura e tutto questo da remoto 

    // Dialog
    $("#button").click(function(){
        $("#dialog").dialog("open")
    })
    $("#dialog").dialog({
        title: "Grazie per averci contattato",
        closeOnEscape: false,
        modal: true,
        autoOpen: false
    })

    // Recensioni
    $(".recensioni").slideToggle()
    $(".recensioni-button").click(function(){
        $(".recensioni").slideToggle()
    })
})