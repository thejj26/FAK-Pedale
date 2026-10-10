class View extends HTMLElement {
    constructor(patchConnection) {
        super();
        this.patchConnection = patchConnection;

        this.attachShadow({ mode: 'open' });
        this.shadowRoot.innerHTML = this.getHTML();
    }

    getHTML() {
        return `
            <style>
                *{
                    margin: 0;
                    padding: 0;
                }

                :host {
                    display: block;
                    width: 100%;
                    height: 100%;
                    max-height: 100%;
                    max-width: 100%;
                    overflow: hidden;
                    position: relative;

                    background: linear-gradient(
                        135deg,
                        #2d2e32 0%,
                        #27282b 25%,
                        #1c1d20 50%,
                        #202124 75%,
                        #2f3035 100%
                    );
                    box-shadow: inset 0 1px 1px rgba(255, 255, 255, 0.1), 
                        inset 0 -1px 2px rgba(0, 0, 0, 0.6),
                        0 8px 24px rgba(0, 0, 0, 0.5);
                    border: 3px solid #141416;
                }


                .container{
                    width: 100%;
                    height: 100%;
                    margin-top: 120px;
                    dispay: flex;
                    flex-direction: column;
                    justify-items: center;
                }

                .container>div{
                    dispay: flex;
                    flex-direction: column;
                    justify-items: center;
                }

                .title{
                    position: absolute;
                    top: 20px;
                    right: 50%;
                    transform: translate(50%, 0);
                    width: 200px;
                    height: auto;
                    -webkit-user-drag: none;

                }
            </style>
            <div class="container">
                <img src="distortion_logo.png" class="title">
                <div class="controls">
                    <div class="gain-volume">
                        <input type="range" min="1" max="100" step="1" class="knob-input" value="10" id="gain" step="1">
                        <input type="range" min="0" max="100" step="1" class="knob-input" value="50" id="volume" step="1">
                    </div>
                    <div class="tresholds">
                    <input type="range" min="0.1" max="1" class="knob-input" value="0.5" id="tresholdP" step="0.01">
                    <input type="range" min="0.1" max="1" class="knob-input" value="0.5" id="tresholdN" step="0.01">
                    </div>
                    <div class="soft-clip">
                        <input type="checkbox" id="softCLip">
                    </div>
                </div>
            </div>
            
        `;
    }
}

window.customElements.define("fak-view", View);

export default function createPatchView(patchConnection) {
    return new View(patchConnection);
}