<script lang="ts">
	let english = true;
	let manifest =  'manifest/manifest-en.json';

	const toggle = () => {
		if (english) {
			manifest = 'manifest/manifest-en.json';
		} else {
			manifest = 'manifest/manifest-de.json';
		}
	}
</script>

<h1>Welcome to SvelteKit</h1>
<p>Install Galaxis</p>

<div class="form-control w-1/4">
	<label class="label cursor-pointer">
		<span class="label-text">German</span>
		<input type="checkbox" class="toggle toggle-sm bg-primary hover:bg-primary/80"
					 bind:checked={english} on:change={toggle} />
		<span class="label-text">English</span>
	</label>
</div>

<div class="form-control w-1/4">
	<esp-web-install-button manifest={manifest}>
		<button class="btn w-32 rounded-full btn-sm btn-primary" slot="activate">Install</button>
	</esp-web-install-button>
</div>

<style lang="postcss">
    :global(html) {
        @apply bg-secondary;
    }
</style>
