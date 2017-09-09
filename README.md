# Sonosthesia-Analyser

Part of the [Sonosthesia](www.sonosthesia.com/home) project.

An audio plugin based on the [JUCE toolkit](href="https://www.juce.com/features") which allows the product to be compatible with a number of standards, most significantly VST and AU. Pre-compiled binaries will be provided soon but you can tweak the JUCE project to your needs if they are not sufficient (and feel free to contribute...).

This project is derived from Adam Stark's [Sound Analyser](http://www.adamstark.co.uk/sound-analyser") project, the source code for which can be found [here](https://github.com/adamstark/Sound-Analyser). In a [conference paper](http://adamstark.co.uk/pdf/papers/nime-2014-sound-analyser.pdf) Adam Stark describes his vision in more detail, a vision which is closely related to that of Sonosthesia.

> Real-time audio analysis has great potential for being used to create musically responsive applications in live performances. There have been many examples of such use, including sound-responsive visualisations, adaptive audio effects and machine musicianship. However, at present, using audio analysis algorithms in live performance requires either some detailed knowledge about the algorithms themselves, or programming – or both. [...] In response, this paper introduces the Sound Analyser – an audio plug-in allowing users to a) select a custom set of audio analyses to be performed in real-time and b) send that information via OSC so that it can easily be used by other systems to develop responsive applications for live performances and installations.

Sound analysis can be performed using a variety of algorithms from the [Gist Library](https://github.com/adamstark/Gist) and others.

## Project Overview

The Sonosthesia-Analyser project expands on the original Sound-Analyser in a number of ways. First by adding new analyses by incorporating the work of a number of other open source projects. Secondly, by allowing the result of audio analyses to be assigned to different OSC targets, control groups and control descriptors. 

It also allows audio analyses to be exposed as **static output channels** to the [Sonosthsia-Hub](https://github.com/jbat100/sonosthesia-hub/tree/develop) (see [Sonosthesia Protocol](www.sonosthesia.com/protocols)). 
