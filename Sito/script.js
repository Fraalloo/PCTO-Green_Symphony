$(document).ready(function(){
    Ae()

    let $links = $(".nav-link")
    
    $links.mouseenter(function(){
        let neonColors = ["#ff00ff", "#00ffff", "#ff0080", "#00ff80", "#8000ff", "#80ff00", "#ff0000", "#00ff00", "#0000ff", "#ffff00", "#ff00ff", "#00ffff", "#ff0080", "#00ff80", "#8000ff", "#80ff00", "#ff8000", "#ff0080", "#ff80ff", "#00ff80"]
        let randomColor = neonColors[Math.floor(Math.random() * neonColors.length)]
        $(this).animate({
            borderColor: randomColor
        }, 300)
    })
    $links.mouseleave(function(){
        $(this).animate({
            borderColor: "#000"
        }, 300)
    })

    // NON FUNGE
    let $logo = $("#logo-sito")

    $logo.mouseenter(function(){
        let neonColors = ["#ff00ff", "#00ffff", "#ff0080", "#00ff80", "#8000ff", "#80ff00", "#ff0000", "#00ff00", "#0000ff", "#ffff00", "#ff00ff", "#00ffff", "#ff0080", "#00ff80", "#8000ff", "#80ff00", "#ff8000", "#ff0080", "#ff80ff", "#00ff80"]
        let randomColor1 = neonColors[Math.floor(Math.random() * neonColors.length)]
        let randomColor2 = neonColors[Math.floor(Math.random() * neonColors.length)]
        let randomColor3 = neonColors[Math.floor(Math.random() * neonColors.length)]
        let randomColor4 = neonColors[Math.floor(Math.random() * neonColors.length)]

        $(this).animate({
            boxShadow: randomColor1 + " 0 -1px 4, " + randomColor2 + "0 -2px 10px, " + randomColor3 + "0 -10px 20px, " + randomColor4 + "0 -18px 40px, 5px 5px 15px 5px rgba(0,0,0,0)"
        }, 300)
    })
    $logo.mouseleave(function(){
        $(this).animate({
            boxShadow: "#FFF 0 -1px 4px, #80ed99 0 -2px 10px, #386641 0 -10px 20px, green 0 -18px 40px, 5px 5px 15px 5px rgba(0,0,0,0)"
        }, 300)
    })
})