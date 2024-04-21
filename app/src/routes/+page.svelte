<script lang="ts">
	let english = true;
	let manifest = 'manifest/manifest-de.json';

	const toggle = () => {
		if (english) {
			manifest = 'manifest/manifest-en.json';
		} else {
			manifest = 'manifest/manifest-de.json';
		}
	};
</script>

<div class="p-10">
	<h1 class="pb-5">Galaxis</h1>
	{#if (english)}
		<div>
			<p>With the help of this website you can install <a href="https://github.com/jrmrtns/galaxis">Galaxis</a>, a game by Ravensburger from 1980, on an ESP32-S3 or ESP32-C3 device.</p>
			<p>The WebSerial protocol is used for this, which is currently only supported by Google Chrome or Edge.</p>
			<ul class="list-inside list-disc">
				<li>Connect an ESP32 board to your computer via a USB cable</li>
				<li>Select the language of the interface below (this is also the language of the game)</li>
				<li>Click on the "Install" button below and follow the instructions</li>
			</ul>
			<p>Have fun</p>
			<h3 class="mb-5 mt-5">Further information</h3>
			<p>The source code and wiring can be found on <a href="https://github.com/jrmrtns/galaxis">GitHub</a></p>
			<p>3D models on <a href="https://www.printables.com/de/model/664089-galaxis">Printables</a> or on <a
				href="https://www.thingiverse.com/thing:6317108">Thingiverse</a></p>
		</div>
	{:else}
		<div>
			<p>Mit Hilfe dieser Website könnt ihr <a href="https://github.com/jrmrtns/galaxis">Galaxis</a>, ein Spiel von
				Ravensburger aus dem Jahr 1980, auf ein ESP32-S3 oder ESP32-C3
				Device installieren.</p>
			<p>Hierfür wird das WebSerial Protokoll verwendet, das aktuell nur Google Chrome oder Edge unterstützen.</p>
			<ul class="list-inside list-disc">
				<li>Verbindet ein ESP32-Board über ein USB Kabel mit eurem Computer</li>
				<li>Wählt unten die Sprache der Oberfläche aus (das ist gleichzeitig die Sprache des Spiels)</li>
				<li>Klickt unten auf den "Installieren" Button unten und folgt den Anweisungen</li>
			</ul>
			<p>Viel Spass</p>
			<h3 class="mb-5 mt-5">Weitere Informationen</h3>
			<p>Der Quellcode und Wiring findet auf <a href="https://github.com/jrmrtns/galaxis">GitHub</a></p>
			<p>3D Modelle auf <a href="https://www.printables.com/de/model/664089-galaxis">Printables</a> oder auf <a
				href="https://www.thingiverse.com/thing:6317108">Thingiverse</a></p>
		</div>
	{/if}
	<div>
		<div class="form-control w-1/4 mt-5 mb-5">
			<label class="label cursor-pointer">
				<span>German</span>
				<input type="checkbox" class="toggle toggle-sm bg-primary hover:bg-primary/80"
							 bind:checked={english} on:change={toggle} />
				<span>English</span>
			</label>
		</div>
	</div>
	<div class="form-control w-1/4">
		<esp-web-install-button manifest={manifest}>
			<button class="btn w-32 rounded-full btn-sm btn-primary mb-10 mt-5" slot="activate">Installieren</button>
		</esp-web-install-button>
	</div>

  <hr />
	<p>
		Installer powered by <a href="https://esphome.github.io/esp-web-tools/">ESP Web Tools</a>.
	</p>
</div>

<style lang="postcss">
    :global(html) {
        @apply bg-secondary;
    }

    :global(a) {
        @apply text-secondary;
    }

    p {
        padding-bottom: 10px;
    }
</style>
