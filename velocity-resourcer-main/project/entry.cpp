#include <pch/stdafx.hpp>

int main( )
{
	rpack::writer writer{};

	// fonts
	writer.add( rpack::fonts::font7::regular, resources::fonts::font7::regular );
	writer.add( rpack::fonts::inter::regular, resources::fonts::inter::regular );
	writer.add( rpack::fonts::inter::bold, resources::fonts::inter::bold );
	writer.add( rpack::fonts::pixel7::smallest, resources::fonts::pixel7::smallest );
	writer.add( rpack::fonts::pixel7::advanced, resources::fonts::pixel7::advanced );
	writer.add( rpack::fonts::weapons::cs2, resources::fonts::weapons::cs2 );

	// icons
	writer.add( rpack::images::icons::logo, resources::images::icons::logo );
	writer.add( rpack::images::icons::user, resources::images::icons::user );
	writer.add( rpack::images::icons::users, resources::images::icons::users );
	writer.add( rpack::images::icons::cog, resources::images::icons::cog );
	writer.add( rpack::images::icons::file, resources::images::icons::file );
	writer.add( rpack::images::icons::skull, resources::images::icons::skull );
	writer.add( rpack::images::icons::weather, resources::images::icons::weather );
	writer.add( rpack::images::icons::brush, resources::images::icons::brush );
	writer.add( rpack::images::icons::crosshair, resources::images::icons::crosshair );
	writer.add( rpack::images::icons::bars, resources::images::icons::bars );

	// particles
	writer.add( rpack::particles::effects::killstars, resources::particles::effects::killstars );
	writer.add( rpack::particles::effects::tracer, resources::particles::effects::tracer );
	writer.add( rpack::particles::effects::sparks, resources::particles::effects::sparks );
	writer.add( rpack::particles::effects::fade, resources::particles::effects::fade );
	writer.add( rpack::particles::effects::halo, resources::particles::effects::halo );
	writer.add( rpack::particles::weather::rain, resources::particles::weather::rain );
	writer.add( rpack::particles::weather::snow, resources::particles::weather::snow );
	writer.add( rpack::particles::weather::stars, resources::particles::weather::stars );

	if ( writer.save( "resources.rpak" ) )
	{
		std::printf( "saved resources.rpak\n" );
	}
	else
	{
		std::printf( "failed to save resources.rpak\n" );
	}

	return std::cin.get( );
}