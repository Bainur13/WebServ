import React from 'react';
import './assets/styles/global.css';
import { Actions } from './actions.js';
import ReactDOM from 'react-dom/client';
import { Homepage }  from './homepage.js';
import { Error404 } from './404.js';
import { CustomPage } from './customPage.js';
import { Uploader } from './uploader.js'
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';

function App()
{
	return (
		<Router>
			<Routes>
				<Route path='/' element={ <Homepage /> }/>
				<Route path='/actions' element={ <Actions /> }/>
				<Route path='/custom_page' element={ <CustomPage /> }/>
				<Route path='/uploader' element={ <Uploader />}/>
				<Route path='*' element={ <Error404 /> }/>
			</Routes>
		</Router>
	);
}

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
