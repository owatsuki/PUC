document.addEventListener("DOMContentLoaded", () => {
    const prefersReducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
    if (prefersReducedMotion) return;

    const parallaxLayers = document.querySelectorAll('.layer-parallax');
    
    let ticking = false;

    window.addEventListener('mousemove', (e) => {
        if (!ticking) {
            window.requestAnimationFrame(() => {
                const x = (window.innerWidth - e.pageX * 2) / 100;
                const y = (window.innerHeight - e.pageY * 2) / 100;

                parallaxLayers.forEach(layer => {
                    const speed = layer.getAttribute('data-speed') || 1;
                    layer.style.transform = `translate(${x * speed}px, ${y * speed}px)`;
                });
                ticking = false;
            });
            ticking = true;
        }
    });
});