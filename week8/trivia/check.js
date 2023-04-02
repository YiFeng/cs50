function choiceAnswer(button, event) {
    if (button.value.toLowerCase() === 'zelda') {
        button.style.backgroundColor='green';
        document.querySelector('#result_choice').textContent='Correct!';
    } else {
        button.style.backgroundColor='red';
        document.querySelector('#result_choice').textContent='InCorrect!';
    }
}

window.addEventListener('load', () => {
    const buttons = document.querySelectorAll('button');
    console.log(buttons);
    for (const button of buttons) {
        if (button.id === "text_check") continue;
        button.addEventListener("click", (event) => {
            choiceAnswer(button, event);
        });
    }
});

/*choiceAnswer.bind(button)*/
/*
button.addEventListener = function(eventType, callback) {
    if (currentEvent.type === eventType) {
        callback(currentEvent);
    }
}
*/

function inputAnswer() {
    var inputtext = document.querySelector('input').value
    if (inputtext.toLowerCase() == 'zelda') {
        document.querySelector('#result_input').textContent='Correct!'
        document.querySelector('#result_input').style.color='green' 
    } else {
        document.querySelector('#result_input').textContent='InCorrect!'
        document.querySelector('#result_input').style.color='red'
    }
}