void RiDeclareDebug(RtString name, RtString declaration)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDeclare ";
		_message << "\"" << name << "\" ";
		_message << "\"" << declaration << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBeginDebug(RtToken name)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBegin ";
		_message << "\"" << name << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiGetContextDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiGetContext ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiContextDebug(RtContextHandle handle)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiContext ";
		_message << handle << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiFrameBeginDebug(RtInt number)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiFrameBegin ";
		_message << number << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiFrameEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiFrameEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiWorldBeginDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiWorldBegin ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiWorldEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiWorldEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiIfBeginDebug(RtString condition)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiIfBegin ";
		_message << "\"" << condition << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiElseIfDebug(RtString condition)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiElseIf ";
		_message << "\"" << condition << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiElseDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiElse ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiIfEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiIfEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiFormatDebug(RtInt xresolution, RtInt yresolution, RtFloat pixelaspectratio)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiFormat ";
		_message << xresolution << " ";
		_message << yresolution << " ";
		_message << pixelaspectratio << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiFrameAspectRatioDebug(RtFloat frameratio)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiFrameAspectRatio ";
		_message << frameratio << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiScreenWindowDebug(RtFloat left, RtFloat right, RtFloat bottom, RtFloat top)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiScreenWindow ";
		_message << left << " ";
		_message << right << " ";
		_message << bottom << " ";
		_message << top << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCropWindowDebug(RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCropWindow ";
		_message << xmin << " ";
		_message << xmax << " ";
		_message << ymin << " ";
		_message << ymax << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProjectionDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProjection ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiClippingDebug(RtFloat cnear, RtFloat cfar)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiClipping ";
		_message << cnear << " ";
		_message << cfar << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiClippingPlaneDebug(RtFloat x, RtFloat y, RtFloat z, RtFloat nx, RtFloat ny, RtFloat nz)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiClippingPlane ";
		_message << x << " ";
		_message << y << " ";
		_message << z << " ";
		_message << nx << " ";
		_message << ny << " ";
		_message << nz << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDepthOfFieldDebug(RtFloat fstop, RtFloat focallength, RtFloat focaldistance)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDepthOfField ";
		_message << fstop << " ";
		_message << focallength << " ";
		_message << focaldistance << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiShutterDebug(RtFloat opentime, RtFloat closetime)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiShutter ";
		_message << opentime << " ";
		_message << closetime << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPixelVarianceDebug(RtFloat variance)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPixelVariance ";
		_message << variance << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPixelSamplesDebug(RtFloat xsamples, RtFloat ysamples)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPixelSamples ";
		_message << xsamples << " ";
		_message << ysamples << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPixelFilterDebug(RtFilterFunc function, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPixelFilter ";
		_message << function << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiExposureDebug(RtFloat gain, RtFloat gamma)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiExposure ";
		_message << gain << " ";
		_message << gamma << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiImagerDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiImager ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiQuantizeDebug(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ditheramplitude)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiQuantize ";
		_message << "\"" << type << "\" ";
		_message << one << " ";
		_message << min << " ";
		_message << max << " ";
		_message << ditheramplitude << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDisplayDebug(RtToken name, RtToken type, RtToken mode, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDisplay ";
		_message << "\"" << name << "\" ";
		_message << "\"" << type << "\" ";
		_message << "\"" << mode << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiGaussianFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiGaussianFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBoxFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBoxFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMitchellFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMitchellFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTriangleFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTriangleFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCatmullRomFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCatmullRomFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSincFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSincFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDiskFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDiskFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBesselFilterDebug(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBesselFilter ";
		_message << x << " ";
		_message << y << " ";
		_message << xwidth << " ";
		_message << ywidth << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiHiderDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiHider ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiColorSamplesDebug(RtInt N, RtFloat nRGB[], RtFloat RGBn[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiColorSamples ";
		_message << N << " ";
		int __nRGB_length = N;
		_message << nRGB;
		int __nRGB_index;
		for(__nRGB_index = 0; __nRGB_index<__nRGB_length; __nRGB_index++)
		{
			_message << nRGB[__nRGB_index];
	}
		int __RGBn_length = N;
		_message << RGBn;
		int __RGBn_index;
		for(__RGBn_index = 0; __RGBn_index<__RGBn_length; __RGBn_index++)
		{
			_message << RGBn[__RGBn_index];
	}
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiRelativeDetailDebug(RtFloat relativedetail)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiRelativeDetail ";
		_message << relativedetail << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiOptionDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiOption ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiAttributeBeginDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiAttributeBegin ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiAttributeEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiAttributeEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiColorDebug(RtColor Cq)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiColor ";
		_message << Cq[0] << " " << Cq[1] << " " << Cq[2];
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiOpacityDebug(RtColor Os)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiOpacity ";
		_message << Os[0] << " " << Os[1] << " " << Os[2];
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTextureCoordinatesDebug(RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTextureCoordinates ";
		_message << s1 << " ";
		_message << t1 << " ";
		_message << s2 << " ";
		_message << t2 << " ";
		_message << s3 << " ";
		_message << t3 << " ";
		_message << s4 << " ";
		_message << t4 << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiLightSourceDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiLightSource ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiAreaLightSourceDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiAreaLightSource ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiIlluminateDebug(RtLightHandle light, RtBoolean onoff)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiIlluminate ";
		_message << light << " ";
		_message << onoff << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSurfaceDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSurface ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDeformationDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDeformation ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDisplacementDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDisplacement ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiAtmosphereDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiAtmosphere ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiInteriorDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiInterior ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiExteriorDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiExterior ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiShaderLayerDebug(RtToken type, RtToken name, RtToken layername, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiShaderLayer ";
		_message << "\"" << type << "\" ";
		_message << "\"" << name << "\" ";
		_message << "\"" << layername << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiConnectShaderLayersDebug(RtToken type, RtToken layer1, RtToken variable1, RtToken layer2, RtToken variable2)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiConnectShaderLayers ";
		_message << "\"" << type << "\" ";
		_message << "\"" << layer1 << "\" ";
		_message << "\"" << variable1 << "\" ";
		_message << "\"" << layer2 << "\" ";
		_message << "\"" << variable2 << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiShadingRateDebug(RtFloat size)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiShadingRate ";
		_message << size << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiShadingInterpolationDebug(RtToken type)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiShadingInterpolation ";
		_message << "\"" << type << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMatteDebug(RtBoolean onoff)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMatte ";
		_message << onoff << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBoundDebug(RtBound bound)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBound ";
		_message << bound[0] << " ";
		_message << bound[1] << " ";
		_message << bound[2] << " ";
		_message << bound[3] << " ";
		_message << bound[4] << " ";
		_message << bound[5] << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDetailDebug(RtBound bound)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDetail ";
		_message << bound[0] << " ";
		_message << bound[1] << " ";
		_message << bound[2] << " ";
		_message << bound[3] << " ";
		_message << bound[4] << " ";
		_message << bound[5] << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDetailRangeDebug(RtFloat offlow, RtFloat onlow, RtFloat onhigh, RtFloat offhigh)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDetailRange ";
		_message << offlow << " ";
		_message << onlow << " ";
		_message << onhigh << " ";
		_message << offhigh << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiGeometricApproximationDebug(RtToken type, RtFloat value)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiGeometricApproximation ";
		_message << "\"" << type << "\" ";
		_message << value << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiOrientationDebug(RtToken orientation)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiOrientation ";
		_message << "\"" << orientation << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiReverseOrientationDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiReverseOrientation ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSidesDebug(RtInt nsides)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSides ";
		_message << nsides << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiIdentityDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiIdentity ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTransformDebug(RtMatrix transform)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTransform ";
		_message << "[";
		int __transform_i, __transform_j;
		for(__transform_j = 0; __transform_j<4; __transform_j++)
			for(__transform_i = 0; __transform_i<4; __transform_i++)
				_message << transform[__transform_j][__transform_i] << " ";
		_message << "]" << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiConcatTransformDebug(RtMatrix transform)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiConcatTransform ";
		_message << "[";
		int __transform_i, __transform_j;
		for(__transform_j = 0; __transform_j<4; __transform_j++)
			for(__transform_i = 0; __transform_i<4; __transform_i++)
				_message << transform[__transform_j][__transform_i] << " ";
		_message << "]" << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPerspectiveDebug(RtFloat fov)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPerspective ";
		_message << fov << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTranslateDebug(RtFloat dx, RtFloat dy, RtFloat dz)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTranslate ";
		_message << dx << " ";
		_message << dy << " ";
		_message << dz << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiRotateDebug(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiRotate ";
		_message << angle << " ";
		_message << dx << " ";
		_message << dy << " ";
		_message << dz << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiScaleDebug(RtFloat sx, RtFloat sy, RtFloat sz)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiScale ";
		_message << sx << " ";
		_message << sy << " ";
		_message << sz << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSkewDebug(RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, RtFloat dx2, RtFloat dy2, RtFloat dz2)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSkew ";
		_message << angle << " ";
		_message << dx1 << " ";
		_message << dy1 << " ";
		_message << dz1 << " ";
		_message << dx2 << " ";
		_message << dy2 << " ";
		_message << dz2 << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCoordinateSystemDebug(RtToken space)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCoordinateSystem ";
		_message << "\"" << space << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCoordSysTransformDebug(RtToken space)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCoordSysTransform ";
		_message << "\"" << space << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTransformPointsDebug(RtToken fromspace, RtToken tospace, RtInt npoints, RtPoint points[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTransformPoints ";
		_message << "\"" << fromspace << "\" ";
		_message << "\"" << tospace << "\" ";
		_message << npoints << " ";
		int __points_length = npoints;
		_message << points;
		int __points_index;
		for(__points_index = 0; __points_index<__points_length; __points_index++)
		{
			_message << points[__points_index][0] << " " << points[__points_index][1] << " " << points[__points_index][2];
	}
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTransformBeginDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTransformBegin ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTransformEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTransformEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiResourceDebug(RtToken handle, RtToken type, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiResource ";
		_message << "\"" << handle << "\" ";
		_message << "\"" << type << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiResourceBeginDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiResourceBegin ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiResourceEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiResourceEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiAttributeDebug(RtToken name, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiAttribute ";
		_message << "\"" << name << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPolygonDebug(RtInt nvertices, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPolygon ";
		_message << nvertices << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = nvertices;
		vertex_size = nvertices;
		facevarying_size = nvertices;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiGeneralPolygonDebug(RtInt nloops, RtInt nverts[], RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiGeneralPolygon ";
		_message << nloops << " ";
		int __nverts_length = nloops;
		_message << nverts;
		int __nverts_index;
		for(__nverts_index = 0; __nverts_index<__nverts_length; __nverts_index++)
		{
			_message << nverts[__nverts_index];
	}
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 0;
		{
			int __i;
			for(__i=0;__i<nloops;__i++)
				varying_size+=nverts[__i];
		}
		vertex_size = varying_size;
		facevarying_size = varying_size;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPointsPolygonsDebug(RtInt npolys, RtInt nverts[], RtInt verts[], RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPointsPolygons ";
		_message << npolys << " ";
		int __nverts_length = npolys;
		_message << nverts;
		int __nverts_index;
		for(__nverts_index = 0; __nverts_index<__nverts_length; __nverts_index++)
		{
			_message << nverts[__nverts_index];
	}
		int __verts_length = 0;
		{
			int __i;
			for(__i=0; __i<npolys; __i++)
				__verts_length+=nverts[__i];
		}
		_message << verts;
		int __verts_index;
		for(__verts_index = 0; __verts_index<__verts_length; __verts_index++)
		{
			_message << verts[__verts_index];
	}
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size=0;
		{
			int __i;
			for(__i=0; __i<__verts_length; __i++)
				if(verts[__i]>varying_size)
					varying_size=verts[__i];
		}
		varying_size+=1;
		vertex_size=varying_size;
		facevarying_size=0;
		{
			int __i;
			for(__i=0; __i<npolys; __i++)
				facevarying_size+=nverts[__i];
		}
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPointsGeneralPolygonsDebug(RtInt npolys, RtInt nloops[], RtInt nverts[], RtInt verts[], RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPointsGeneralPolygons ";
		_message << npolys << " ";
		int __nloops_length = npolys;
		_message << nloops;
		int __nloops_index;
		for(__nloops_index = 0; __nloops_index<__nloops_length; __nloops_index++)
		{
			_message << nloops[__nloops_index];
	}
		int __nverts_length = 0;
		{
			int __i;
			for(__i=0; __i<npolys; __i++)
				__nverts_length+=nloops[__i];
		}
		_message << nverts;
		int __nverts_index;
		for(__nverts_index = 0; __nverts_index<__nverts_length; __nverts_index++)
		{
			_message << nverts[__nverts_index];
	}
		int __verts_length = 0;
		{
			int __i;
			for(__i=0; __i<__nverts_length; __i++)
				__verts_length+=nverts[__i];
		}
		_message << verts;
		int __verts_index;
		for(__verts_index = 0; __verts_index<__verts_length; __verts_index++)
		{
			_message << verts[__verts_index];
	}
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size=0;
		{
			int __i;
			for(__i=0; __i<__verts_length; __i++)
				if(verts[__i]>varying_size)
					varying_size=verts[__i];
		}
		varying_size+=1;
		vertex_size=varying_size;
		facevarying_size=0;
		{
			int __i;
			for(__i=0; __i<npolys; __i++)
				facevarying_size+=nverts[__i];
		}
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBasisDebug(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBasis ";
		_message << "[";
		int __ubasis_i, __ubasis_j;
		for(__ubasis_j = 0; __ubasis_j<4; __ubasis_j++)
			for(__ubasis_i = 0; __ubasis_i<4; __ubasis_i++)
				_message << ubasis[__ubasis_j][__ubasis_i] << " ";
		_message << "]" << " ";
		_message << ustep << " ";
		_message << "[";
		int __vbasis_i, __vbasis_j;
		for(__vbasis_j = 0; __vbasis_j<4; __vbasis_j++)
			for(__vbasis_i = 0; __vbasis_i<4; __vbasis_i++)
				_message << vbasis[__vbasis_j][__vbasis_i] << " ";
		_message << "]" << " ";
		_message << vstep << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPatchDebug(RtToken type, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPatch ";
		_message << "\"" << type << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		if(strcmp(type, "bicubic")==0)
			vertex_size=16;
		facevarying_size = varying_size;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPatchMeshDebug(RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPatchMesh ";
		_message << "\"" << type << "\" ";
		_message << nu << " ";
		_message << "\"" << uwrap << "\" ";
		_message << nv << " ";
		_message << "\"" << vwrap << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;

		if(strcmp(type, "bilinear")==0)
		{
			if(strcmp(uwrap, "periodic")==0)
				uniform_size = nu;
			else
				uniform_size = nu-1;
			if(strcmp(vwrap, "periodic")==0)
				uniform_size *= nv;
			else
				uniform_size *= nv-1;
		}
		else
		{
			int ustep = QGetRenderContext() ->pattrCurrent()->GetIntegerAttribute( "System", "BasisStep" ) [ 0 ];
			int vstep = QGetRenderContext() ->pattrCurrent()->GetIntegerAttribute( "System", "BasisStep" ) [ 1 ];
			if(strcmp(uwrap, "periodic")==0)
				uniform_size = nu/ustep;
			else
				uniform_size = (nu-4)/ustep;
			if(strcmp(vwrap, "periodic")==0)
				uniform_size *= nv/vstep;
			else
				uniform_size *= (nv-4)/vstep;
		}

		if(strcmp(type, "bilinear")==0)
			varying_size = nu*nv;
		else
		{
			int ustep = QGetRenderContext() ->pattrCurrent()->GetIntegerAttribute( "System", "BasisStep" ) [ 0 ];
			int vstep = QGetRenderContext() ->pattrCurrent()->GetIntegerAttribute( "System", "BasisStep" ) [ 1 ];
			varying_size = (nu/ustep)*(nv/vstep);
		}
		vertex_size=nu*nv;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiNuPatchDebug(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin, RtFloat vmax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiNuPatch ";
		_message << nu << " ";
		_message << uorder << " ";
		int __uknot_length = nu + uorder;
		_message << uknot;
		int __uknot_index;
		for(__uknot_index = 0; __uknot_index<__uknot_length; __uknot_index++)
		{
			_message << uknot[__uknot_index];
	}
		_message << umin << " ";
		_message << umax << " ";
		_message << nv << " ";
		_message << vorder << " ";
		int __vknot_length = nv + vorder;
		_message << vknot;
		int __vknot_index;
		for(__vknot_index = 0; __vknot_index<__vknot_length; __vknot_index++)
		{
			_message << vknot[__vknot_index];
	}
		_message << vmin << " ";
		_message << vmax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		uniform_size=(1+nu-uorder+1)*(1+nv-vorder+1);
		varying_size=(1+nu-uorder+1)*(1+nv-vorder+1);
		vertex_size=nu*nv;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTrimCurveDebug(RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[], RtFloat min[], RtFloat max[], RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTrimCurve ";
		_message << nloops << " ";
		int __ncurves_length = nloops;
		_message << ncurves;
		int __ncurves_index;
		for(__ncurves_index = 0; __ncurves_index<__ncurves_length; __ncurves_index++)
		{
			_message << ncurves[__ncurves_index];
	}
		int __order_length = 0;
		{
			int __i;
			for(__i=0; __i<nloops; __i++)
				__order_length+=ncurves[__i];
		}
		_message << order;
		int __order_index;
		for(__order_index = 0; __order_index<__order_length; __order_index++)
		{
			_message << order[__order_index];
	}
		int __knot_length = 0;
		{
			int __i;
			for(__i=0; __i<__order_length; __i++)
				__knot_length+=order[__i]+n[__i];
		}
		_message << knot;
		int __knot_index;
		for(__knot_index = 0; __knot_index<__knot_length; __knot_index++)
		{
			_message << knot[__knot_index];
	}
		int __min_length = __order_length;
		_message << min;
		int __min_index;
		for(__min_index = 0; __min_index<__min_length; __min_index++)
		{
			_message << min[__min_index];
	}
		int __max_length = __order_length;
		_message << max;
		int __max_index;
		for(__max_index = 0; __max_index<__max_length; __max_index++)
		{
			_message << max[__max_index];
	}
		int __n_length = __order_length;
		_message << n;
		int __n_index;
		for(__n_index = 0; __n_index<__n_length; __n_index++)
		{
			_message << n[__n_index];
	}
		int __u_length = 0;
		{
			int __i;
			for(__i=0; __i<__order_length; __i++)
				__u_length+=n[__i];
		}
		_message << u;
		int __u_index;
		for(__u_index = 0; __u_index<__u_length; __u_index++)
		{
			_message << u[__u_index];
	}
		int __v_length = __u_length;
		_message << v;
		int __v_index;
		for(__v_index = 0; __v_index<__v_length; __v_index++)
		{
			_message << v[__v_index];
	}
		int __w_length = __u_length;
		_message << w;
		int __w_index;
		for(__w_index = 0; __w_index<__w_length; __w_index++)
		{
			_message << w[__w_index];
	}
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSubdivisionMeshDebug(RtToken scheme, RtInt nfaces, RtInt nvertices[], RtInt vertices[], RtInt ntags, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSubdivisionMesh ";
		_message << "\"" << scheme << "\" ";
		_message << nfaces << " ";
		int __nvertices_length = nfaces;
		_message << nvertices;
		int __nvertices_index;
		for(__nvertices_index = 0; __nvertices_index<__nvertices_length; __nvertices_index++)
		{
			_message << nvertices[__nvertices_index];
	}
		int __vertices_length = 0;
		{
			int __i;
			for(__i=0; __i<nfaces; __i++)
				__vertices_length+=nvertices[__i];
		}
		_message << vertices;
		int __vertices_index;
		for(__vertices_index = 0; __vertices_index<__vertices_length; __vertices_index++)
		{
			_message << vertices[__vertices_index];
	}
		_message << ntags << " ";
		int __tags_length = ntags;		_message << tags;
		int __tags_index;
		for(__tags_index = 0; __tags_index<__tags_length; __tags_index++)
		{
			_message << tags[__tags_index];
	}
		int __nargs_length = ntags*2;
		_message << nargs;
		int __nargs_index;
		for(__nargs_index = 0; __nargs_index<__nargs_length; __nargs_index++)
		{
			_message << nargs[__nargs_index];
	}
		int __intargs_length = 0;
		{
			int __i;
			for(__i=0; __i<ntags*2; __i+=2)
				__intargs_length+=nargs[__i];
		}
		_message << intargs;
		int __intargs_index;
		for(__intargs_index = 0; __intargs_index<__intargs_length; __intargs_index++)
		{
			_message << intargs[__intargs_index];
	}
		int __floatargs_length = 0;
		{
			int __i;
			for(__i=0; __i<ntags*2; __i+=2)
				__floatargs_length+=nargs[__i+1];
		}
		_message << floatargs;
		int __floatargs_index;
		for(__floatargs_index = 0; __floatargs_index<__floatargs_length; __floatargs_index++)
		{
			_message << floatargs[__floatargs_index];
	}
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size=0;
		{
			int __i;
			for(__i=0; __i<__vertices_length; __i++)
				if(vertices[__i]>varying_size)
					varying_size=vertices[__i];
		}
		varying_size+=1;
		vertex_size=varying_size;
		facevarying_size=0;
		{
			int __i;
			for(__i=0; __i<nfaces; __i++)
				facevarying_size+=nvertices[__i];
		}
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSphereDebug(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSphere ";
		_message << radius << " ";
		_message << zmin << " ";
		_message << zmax << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiConeDebug(RtFloat height, RtFloat radius, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCone ";
		_message << height << " ";
		_message << radius << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCylinderDebug(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCylinder ";
		_message << radius << " ";
		_message << zmin << " ";
		_message << zmax << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiHyperboloidDebug(RtPoint point1, RtPoint point2, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiHyperboloid ";
		_message << point1[0] << " " << point1[1] << " " << point1[2];
		_message << point2[0] << " " << point2[1] << " " << point2[2];
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiParaboloidDebug(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiParaboloid ";
		_message << rmax << " ";
		_message << zmin << " ";
		_message << zmax << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiDiskDebug(RtFloat height, RtFloat radius, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiDisk ";
		_message << height << " ";
		_message << radius << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiTorusDebug(RtFloat majorrad, RtFloat minorrad, RtFloat phimin, RtFloat phimax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiTorus ";
		_message << majorrad << " ";
		_message << minorrad << " ";
		_message << phimin << " ";
		_message << phimax << " ";
		_message << thetamax << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = 4;
		vertex_size = 4;
		facevarying_size = 4;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiPointsDebug(RtInt npoints, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiPoints ";
		_message << npoints << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		varying_size = npoints;
		vertex_size = npoints;
		facevarying_size = npoints;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiCurvesDebug(RtToken type, RtInt ncurves, RtInt nvertices[], RtToken wrap, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiCurves ";
		_message << "\"" << type << "\" ";
		_message << ncurves << " ";
		int __nvertices_length = ncurves;
		_message << nvertices;
		int __nvertices_index;
		for(__nvertices_index = 0; __nvertices_index<__nvertices_length; __nvertices_index++)
		{
			_message << nvertices[__nvertices_index];
	}
		_message << "\"" << wrap << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		uniform_size = ncurves;
		varying_size = 0;
		{
			int __i;
			for(__i=0; __i<__nvertices_length; __i++)
			{
				if(strcmp(type, "cubic")==0)
				{
					int step = QGetRenderContext() ->pattrCurrent()->GetIntegerAttribute( "System", "BasisStep" ) [ 0 ];
					if(strcmp(wrap, "periodic")==0)
						varying_size+=nvertices[__i]/step;
					else
						varying_size+=((nvertices[__i]-4)/step)+1;
				}
				else
				{
					if(strcmp(wrap, "periodic")==0)
						varying_size+=nvertices[__i];
					else
						varying_size+=nvertices[__i]-1;
				}
				varying_size+=1;
			}
		}
		vertex_size = 0;
		{
			int __i;
			for(__i=0; __i<ncurves; __i++)
				vertex_size+=nvertices[__i];
		}
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiBlobbyDebug(RtInt nleaf, RtInt ncode, RtInt code[], RtInt nflt, RtFloat flt[], RtInt nstr, RtToken str[], RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiBlobby ";
		_message << nleaf << " ";
		_message << ncode << " ";
		int __code_length = ncode;
		_message << code;
		int __code_index;
		for(__code_index = 0; __code_index<__code_length; __code_index++)
		{
			_message << code[__code_index];
	}
		_message << nflt << " ";
		int __flt_length = nflt;
		_message << flt;
		int __flt_index;
		for(__flt_index = 0; __flt_index<__flt_length; __flt_index++)
		{
			_message << flt[__flt_index];
	}
		_message << nstr << " ";
		int __str_length = nstr;
		_message << str;
		int __str_index;
		for(__str_index = 0; __str_index<__str_length; __str_index++)
		{
			_message << str[__str_index];
	}
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProceduralDebug(RtPointer data, RtBound bound, RtProcSubdivFunc refineproc, RtProcFreeFunc freeproc)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProcedural ";
		_message << data << " ";
		_message << bound[0] << " ";
		_message << bound[1] << " ";
		_message << bound[2] << " ";
		_message << bound[3] << " ";
		_message << bound[4] << " ";
		_message << bound[5] << " ";
		_message << refineproc << " ";
		_message << freeproc << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProcFreeDebug(RtPointer data)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProcFree ";
		_message << data << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProcDelayedReadArchiveDebug(RtPointer data, RtFloat detail)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProcDelayedReadArchive ";
		_message << data << " ";
		_message << detail << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProcRunProgramDebug(RtPointer data, RtFloat detail)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProcRunProgram ";
		_message << data << " ";
		_message << detail << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiProcDynamicLoadDebug(RtPointer data, RtFloat detail)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiProcDynamicLoad ";
		_message << data << " ";
		_message << detail << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiGeometryDebug(RtToken type, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiGeometry ";
		_message << "\"" << type << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSolidBeginDebug(RtToken type)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSolidBegin ";
		_message << "\"" << type << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiSolidEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiSolidEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiObjectBeginDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiObjectBegin ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiObjectEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiObjectEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiObjectInstanceDebug(RtObjectHandle handle)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiObjectInstance ";
		_message << handle << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMotionBeginDebug(RtInt N,  ...)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMotionBegin ";
		_message << N << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMotionBeginVDebug(RtInt N, RtFloat times[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMotionBeginV ";
		_message << N << " ";
		int __times_length = N;
		_message << times;
		int __times_index;
		for(__times_index = 0; __times_index<__times_length; __times_index++)
		{
			_message << times[__times_index];
	}
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMotionEndDebug()
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMotionEnd ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeTextureDebug(RtString imagefile, RtString texturefile, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeTexture ";
		_message << "\"" << imagefile << "\" ";
		_message << "\"" << texturefile << "\" ";
		_message << "\"" << swrap << "\" ";
		_message << "\"" << twrap << "\" ";
		_message << filterfunc << " ";
		_message << swidth << " ";
		_message << twidth << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeBumpDebug(RtString imagefile, RtString bumpfile, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeBump ";
		_message << "\"" << imagefile << "\" ";
		_message << "\"" << bumpfile << "\" ";
		_message << "\"" << swrap << "\" ";
		_message << "\"" << twrap << "\" ";
		_message << filterfunc << " ";
		_message << swidth << " ";
		_message << twidth << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeLatLongEnvironmentDebug(RtString imagefile, RtString reflfile, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeLatLongEnvironment ";
		_message << "\"" << imagefile << "\" ";
		_message << "\"" << reflfile << "\" ";
		_message << filterfunc << " ";
		_message << swidth << " ";
		_message << twidth << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeCubeFaceEnvironmentDebug(RtString px, RtString nx, RtString py, RtString ny, RtString pz, RtString nz, RtString reflfile, RtFloat fov, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeCubeFaceEnvironment ";
		_message << "\"" << px << "\" ";
		_message << "\"" << nx << "\" ";
		_message << "\"" << py << "\" ";
		_message << "\"" << ny << "\" ";
		_message << "\"" << pz << "\" ";
		_message << "\"" << nz << "\" ";
		_message << "\"" << reflfile << "\" ";
		_message << fov << " ";
		_message << filterfunc << " ";
		_message << swidth << " ";
		_message << twidth << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeShadowDebug(RtString picfile, RtString shadowfile, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeShadow ";
		_message << "\"" << picfile << "\" ";
		_message << "\"" << shadowfile << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiMakeOcclusionDebug(RtInt npics, RtString picfiles[], RtString shadowfile, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiMakeOcclusion ";
		_message << npics << " ";
		int __picfiles_length = npics;
		_message << picfiles;
		int __picfiles_index;
		for(__picfiles_index = 0; __picfiles_index<__picfiles_length; __picfiles_index++)
		{
			_message << picfiles[__picfiles_index];
	}
		_message << "\"" << shadowfile << "\" ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiErrorHandlerDebug(RtErrorFunc handler)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiErrorHandler ";
		_message << handler << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiErrorIgnoreDebug(RtInt code, RtInt severity, RtString message)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiErrorIgnore ";
		_message << code << " ";
		_message << severity << " ";
		_message << "\"" << message << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiErrorPrintDebug(RtInt code, RtInt severity, RtString message)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiErrorPrint ";
		_message << code << " ";
		_message << severity << " ";
		_message << "\"" << message << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiErrorAbortDebug(RtInt code, RtInt severity, RtString message)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiErrorAbort ";
		_message << code << " ";
		_message << severity << " ";
		_message << "\"" << message << "\" ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiArchiveRecordDebug(RtToken type, char * format,  ...)
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiArchiveRecord ";
		_message << "\"" << type << "\" ";
		_message << format << " ";
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}
void RiReadArchiveDebug(RtToken name, RtArchiveCallback callback, RtInt count, RtToken tokens[], RtPointer values[])
{
	if(QGetRenderContext() == 0 || !QGetRenderContext()->poptCurrent()) return;
	const TqInt* poptEcho = QGetRenderContext()->poptCurrent()->GetIntegerOption( "statistics", "echoapi" );
	if(poptEcho != 0 && *poptEcho != 0 )
	{
		std::stringstream _message;
		_message << "RiReadArchive ";
		_message << "\"" << name << "\" ";
		_message << callback << " ";
		// Output the plist here.

		int uniform_size = 1;
		int varying_size = 1;
		int vertex_size = 1;
		int facevarying_size = 1;
		int facevertex_size = 1;
		DebugPlist(count, tokens, values, SqInterpClassCounts(uniform_size, varying_size,
			vertex_size, facevarying_size, facevertex_size), _message);
		Aqsis::log() <<  _message.str().c_str() << std::endl;
	}
}

#define DEBUG_RIDECLARE RiDeclareDebug(name, declaration);

#define DEBUG_RIBEGIN RiBeginDebug(name);

#define DEBUG_RIEND RiEndDebug();

#define DEBUG_RIGETCONTEXT RiGetContextDebug();

#define DEBUG_RICONTEXT RiContextDebug(handle);

#define DEBUG_RIFRAMEBEGIN RiFrameBeginDebug(number);

#define DEBUG_RIFRAMEEND RiFrameEndDebug();

#define DEBUG_RIWORLDBEGIN RiWorldBeginDebug();

#define DEBUG_RIWORLDEND RiWorldEndDebug();

#define DEBUG_RIIFBEGIN RiIfBeginDebug(condition);

#define DEBUG_RIELSEIF RiElseIfDebug(condition);

#define DEBUG_RIELSE RiElseDebug();

#define DEBUG_RIIFEND RiIfEndDebug();

#define DEBUG_RIFORMAT RiFormatDebug(xresolution, yresolution, pixelaspectratio);

#define DEBUG_RIFRAMEASPECTRATIO RiFrameAspectRatioDebug(frameratio);

#define DEBUG_RISCREENWINDOW RiScreenWindowDebug(left, right, bottom, top);

#define DEBUG_RICROPWINDOW RiCropWindowDebug(xmin, xmax, ymin, ymax);

#define DEBUG_RIPROJECTION RiProjectionDebug(name, count, tokens, values);

#define DEBUG_RICLIPPING RiClippingDebug(cnear, cfar);

#define DEBUG_RICLIPPINGPLANE RiClippingPlaneDebug(x, y, z, nx, ny, nz);

#define DEBUG_RIDEPTHOFFIELD RiDepthOfFieldDebug(fstop, focallength, focaldistance);

#define DEBUG_RISHUTTER RiShutterDebug(opentime, closetime);

#define DEBUG_RIPIXELVARIANCE RiPixelVarianceDebug(variance);

#define DEBUG_RIPIXELSAMPLES RiPixelSamplesDebug(xsamples, ysamples);

#define DEBUG_RIPIXELFILTER RiPixelFilterDebug(function, xwidth, ywidth);

#define DEBUG_RIEXPOSURE RiExposureDebug(gain, gamma);

#define DEBUG_RIIMAGER RiImagerDebug(name, count, tokens, values);

#define DEBUG_RIQUANTIZE RiQuantizeDebug(type, one, min, max, ditheramplitude);

#define DEBUG_RIDISPLAY RiDisplayDebug(name, type, mode, count, tokens, values);

#define DEBUG_RIGAUSSIANFILTER RiGaussianFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RIBOXFILTER RiBoxFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RIMITCHELLFILTER RiMitchellFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RITRIANGLEFILTER RiTriangleFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RICATMULLROMFILTER RiCatmullRomFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RISINCFILTER RiSincFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RIDISKFILTER RiDiskFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RIBESSELFILTER RiBesselFilterDebug(x, y, xwidth, ywidth);

#define DEBUG_RIHIDER RiHiderDebug(name, count, tokens, values);

#define DEBUG_RICOLORSAMPLES RiColorSamplesDebug(N, nRGB, RGBn);

#define DEBUG_RIRELATIVEDETAIL RiRelativeDetailDebug(relativedetail);

#define DEBUG_RIOPTION RiOptionDebug(name, count, tokens, values);

#define DEBUG_RIATTRIBUTEBEGIN RiAttributeBeginDebug();

#define DEBUG_RIATTRIBUTEEND RiAttributeEndDebug();

#define DEBUG_RICOLOR RiColorDebug(Cq);

#define DEBUG_RIOPACITY RiOpacityDebug(Os);

#define DEBUG_RITEXTURECOORDINATES RiTextureCoordinatesDebug(s1, t1, s2, t2, s3, t3, s4, t4);

#define DEBUG_RILIGHTSOURCE RiLightSourceDebug(name, count, tokens, values);

#define DEBUG_RIAREALIGHTSOURCE RiAreaLightSourceDebug(name, count, tokens, values);

#define DEBUG_RIILLUMINATE RiIlluminateDebug(light, onoff);

#define DEBUG_RISURFACE RiSurfaceDebug(name, count, tokens, values);

#define DEBUG_RIDEFORMATION RiDeformationDebug(name, count, tokens, values);

#define DEBUG_RIDISPLACEMENT RiDisplacementDebug(name, count, tokens, values);

#define DEBUG_RIATMOSPHERE RiAtmosphereDebug(name, count, tokens, values);

#define DEBUG_RIINTERIOR RiInteriorDebug(name, count, tokens, values);

#define DEBUG_RIEXTERIOR RiExteriorDebug(name, count, tokens, values);

#define DEBUG_RISHADERLAYER RiShaderLayerDebug(type, name, layername, count, tokens, values);

#define DEBUG_RICONNECTSHADERLAYERS RiConnectShaderLayersDebug(type, layer1, variable1, layer2, variable2);

#define DEBUG_RISHADINGRATE RiShadingRateDebug(size);

#define DEBUG_RISHADINGINTERPOLATION RiShadingInterpolationDebug(type);

#define DEBUG_RIMATTE RiMatteDebug(onoff);

#define DEBUG_RIBOUND RiBoundDebug(bound);

#define DEBUG_RIDETAIL RiDetailDebug(bound);

#define DEBUG_RIDETAILRANGE RiDetailRangeDebug(offlow, onlow, onhigh, offhigh);

#define DEBUG_RIGEOMETRICAPPROXIMATION RiGeometricApproximationDebug(type, value);

#define DEBUG_RIORIENTATION RiOrientationDebug(orientation);

#define DEBUG_RIREVERSEORIENTATION RiReverseOrientationDebug();

#define DEBUG_RISIDES RiSidesDebug(nsides);

#define DEBUG_RIIDENTITY RiIdentityDebug();

#define DEBUG_RITRANSFORM RiTransformDebug(transform);

#define DEBUG_RICONCATTRANSFORM RiConcatTransformDebug(transform);

#define DEBUG_RIPERSPECTIVE RiPerspectiveDebug(fov);

#define DEBUG_RITRANSLATE RiTranslateDebug(dx, dy, dz);

#define DEBUG_RIROTATE RiRotateDebug(angle, dx, dy, dz);

#define DEBUG_RISCALE RiScaleDebug(sx, sy, sz);

#define DEBUG_RISKEW RiSkewDebug(angle, dx1, dy1, dz1, dx2, dy2, dz2);

#define DEBUG_RICOORDINATESYSTEM RiCoordinateSystemDebug(space);

#define DEBUG_RICOORDSYSTRANSFORM RiCoordSysTransformDebug(space);

#define DEBUG_RITRANSFORMPOINTS RiTransformPointsDebug(fromspace, tospace, npoints, points);

#define DEBUG_RITRANSFORMBEGIN RiTransformBeginDebug();

#define DEBUG_RITRANSFORMEND RiTransformEndDebug();

#define DEBUG_RIRESOURCE RiResourceDebug(handle, type, count, tokens, values);

#define DEBUG_RIRESOURCEBEGIN RiResourceBeginDebug();

#define DEBUG_RIRESOURCEEND RiResourceEndDebug();

#define DEBUG_RIATTRIBUTE RiAttributeDebug(name, count, tokens, values);

#define DEBUG_RIPOLYGON RiPolygonDebug(nvertices, count, tokens, values);

#define DEBUG_RIGENERALPOLYGON RiGeneralPolygonDebug(nloops, nverts, count, tokens, values);

#define DEBUG_RIPOINTSPOLYGONS RiPointsPolygonsDebug(npolys, nverts, verts, count, tokens, values);

#define DEBUG_RIPOINTSGENERALPOLYGONS RiPointsGeneralPolygonsDebug(npolys, nloops, nverts, verts, count, tokens, values);

#define DEBUG_RIBASIS RiBasisDebug(ubasis, ustep, vbasis, vstep);

#define DEBUG_RIPATCH RiPatchDebug(type, count, tokens, values);

#define DEBUG_RIPATCHMESH RiPatchMeshDebug(type, nu, uwrap, nv, vwrap, count, tokens, values);

#define DEBUG_RINUPATCH RiNuPatchDebug(nu, uorder, uknot, umin, umax, nv, vorder, vknot, vmin, vmax, count, tokens, values);

#define DEBUG_RITRIMCURVE RiTrimCurveDebug(nloops, ncurves, order, knot, min, max, n, u, v, w);

#define DEBUG_RISUBDIVISIONMESH RiSubdivisionMeshDebug(scheme, nfaces, nvertices, vertices, ntags, tags, nargs, intargs, floatargs, count, tokens, values);

#define DEBUG_RISPHERE RiSphereDebug(radius, zmin, zmax, thetamax, count, tokens, values);

#define DEBUG_RICONE RiConeDebug(height, radius, thetamax, count, tokens, values);

#define DEBUG_RICYLINDER RiCylinderDebug(radius, zmin, zmax, thetamax, count, tokens, values);

#define DEBUG_RIHYPERBOLOID RiHyperboloidDebug(point1, point2, thetamax, count, tokens, values);

#define DEBUG_RIPARABOLOID RiParaboloidDebug(rmax, zmin, zmax, thetamax, count, tokens, values);

#define DEBUG_RIDISK RiDiskDebug(height, radius, thetamax, count, tokens, values);

#define DEBUG_RITORUS RiTorusDebug(majorrad, minorrad, phimin, phimax, thetamax, count, tokens, values);

#define DEBUG_RIPOINTS RiPointsDebug(npoints, count, tokens, values);

#define DEBUG_RICURVES RiCurvesDebug(type, ncurves, nvertices, wrap, count, tokens, values);

#define DEBUG_RIBLOBBY RiBlobbyDebug(nleaf, ncode, code, nflt, flt, nstr, str, count, tokens, values);

#define DEBUG_RIPROCEDURAL RiProceduralDebug(data, bound, refineproc, freeproc);

#define DEBUG_RIPROCFREE RiProcFreeDebug(data);

#define DEBUG_RIPROCDELAYEDREADARCHIVE RiProcDelayedReadArchiveDebug(data, detail);

#define DEBUG_RIPROCRUNPROGRAM RiProcRunProgramDebug(data, detail);

#define DEBUG_RIPROCDYNAMICLOAD RiProcDynamicLoadDebug(data, detail);

#define DEBUG_RIGEOMETRY RiGeometryDebug(type, count, tokens, values);

#define DEBUG_RISOLIDBEGIN RiSolidBeginDebug(type);

#define DEBUG_RISOLIDEND RiSolidEndDebug();

#define DEBUG_RIOBJECTBEGIN RiObjectBeginDebug();

#define DEBUG_RIOBJECTEND RiObjectEndDebug();

#define DEBUG_RIOBJECTINSTANCE RiObjectInstanceDebug(handle);

#define DEBUG_RIMOTIONBEGIN RiMotionBeginDebug(N);

#define DEBUG_RIMOTIONBEGINV RiMotionBeginVDebug(N, times);

#define DEBUG_RIMOTIONEND RiMotionEndDebug();

#define DEBUG_RIMAKETEXTURE RiMakeTextureDebug(imagefile, texturefile, swrap, twrap, filterfunc, swidth, twidth, count, tokens, values);

#define DEBUG_RIMAKEBUMP RiMakeBumpDebug(imagefile, bumpfile, swrap, twrap, filterfunc, swidth, twidth, count, tokens, values);

#define DEBUG_RIMAKELATLONGENVIRONMENT RiMakeLatLongEnvironmentDebug(imagefile, reflfile, filterfunc, swidth, twidth, count, tokens, values);

#define DEBUG_RIMAKECUBEFACEENVIRONMENT RiMakeCubeFaceEnvironmentDebug(px, nx, py, ny, pz, nz, reflfile, fov, filterfunc, swidth, twidth, count, tokens, values);

#define DEBUG_RIMAKESHADOW RiMakeShadowDebug(picfile, shadowfile, count, tokens, values);

#define DEBUG_RIMAKEOCCLUSION RiMakeOcclusionDebug(npics, picfiles, shadowfile, count, tokens, values);

#define DEBUG_RIERRORHANDLER RiErrorHandlerDebug(handler);

#define DEBUG_RIERRORIGNORE RiErrorIgnoreDebug(code, severity, message);

#define DEBUG_RIERRORPRINT RiErrorPrintDebug(code, severity, message);

#define DEBUG_RIERRORABORT RiErrorAbortDebug(code, severity, message);

#define DEBUG_RIARCHIVERECORD RiArchiveRecordDebug(type, format);

#define DEBUG_RIREADARCHIVE RiReadArchiveDebug(name, callback, count, tokens, values);
