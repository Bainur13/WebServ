import React from 'react';
import './assets/styles/global.css';
import { Actions } from './actions.js';
import ReactDOM from 'react-dom/client';
import { Homepage }  from './homepage.js';
import { Error404 } from './404.js';
import { CustomPage } from './customPage.js';
import { Uploader } from './uploader.js'
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import { ChooseTheme } from './choose_theme.js';
import { Success } from './success.js';
import { Fail } from './fail.js'
import { Login } from './login.js'
import { CreateAccount } from './signup.js';
import { FetchAndDeleteFiles } from './delete_file.js';

function App()
{
	return (
		<Router>
			<Routes>
				<Route path='/' element={ <Homepage /> }/>
				<Route path='/actions' element={ <Actions /> }/>
				<Route path='/action/custom_page' element={ <CustomPage /> }/>
				<Route path='/action/uploader' element={ <Uploader /> }/>
				<Route path='/action/choose_theme' element={ <ChooseTheme /> }/>
				<Route path='/success' element={ <Success /> }/>
				<Route path='/fail' element={ <Fail /> }/>
				<Route path='/login' element={ <Login />}/>
				<Route path='/createaccount' element= {<CreateAccount />} />
				<Route path='/action/delete_file' element= {<FetchAndDeleteFiles />} />
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
