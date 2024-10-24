import React, { useState } from "react";
import { NavBar } from "./navbar";
import { Footer } from "./footer";
import './assets/styles/custompage.css'

export function CustomPage()
{
	return (
		<>
			<NavBar />
			<main>
			<CustomPageForm />
			</main>
			<Footer />
		</>
	);
}

export function CustomPageForm()
{
	const [activeForm, setActiveForm] = useState(null);

	const handleRetour = () => {
		setActiveForm(null);
	};

	return (
		<>
			{!activeForm && (
			<>
				<h1 id='choiceTitle'>Choose a form</h1>
				<div id='choices'>
					<button className='choiceBtn' onClick={() => setActiveForm('Get form')}>Get Method Form</button>
					<button className='choiceBtn' onClick={() => setActiveForm('Post form')}>Post Method Form</button>
				</div>
			</>
			)}

			{activeForm && (
			<div id="returnBtnDiv">
				<button id='returnBtn' onClick={handleRetour}> &#x2190; Retour </button>
			</div>
			)}

			<CustomForm activeForm={activeForm}/>
		</>
	);
}

function CustomForm( {activeForm} )
{
	const methods = { 'Get form' : 'get', 'Post form' : 'post'};
	const method = methods[activeForm];
	return ( activeForm &&
			<>
			<h2 className="formTitle">{activeForm}</h2>
			<form className='customPageForms' action='/createcustom' method={method}>
				<div id="internFormDiv">
					<div id="formLabels">
						<label>
							Nom :
						</label>
						<label>
							Prenom :
						</label>
						<label>
							Date de naissance :
						</label>
					</div>
					<div id="formInputs">
						<input type="text" name="firstName" required/>
						<input type="text" name="lastName" required/>
						<input type="date" name="birthday" required/>
					</div>
				</div>
				<button id='formSubmitBtn' type="submitBtn">Create custom page</button>
			</form>
			</>
	)
}
